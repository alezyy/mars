<?php

/**
 * Custom date filter, used exposed in the Clicks listing.
 * Provides two select boxes for filtering results by month and year.
 * Shows only the years for which there are clicks defined.
 *
 * If there is only one year to be displayed in the select box,
 * then the year is shown INSTEAD of the select box.
 */
class affiliate_ng_handler_filter_date extends views_handler_filter {
  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    return $this->value['month'] . '/' . $this->value['year'];
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['value'] = array(
      'contains' => array(
        'month' => array('default' => ''),
        'year' => array('default' => ''),
      ),
    );
    $options['multiple_months'] = array('default' => 0);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['multiple_months'] = array(
      '#type' => 'checkbox',
      '#title' => t('Multiple months'),
      '#description' => t('Allow multiple months to be selected'),
      '#default_value' => $this->options['multiple_months'],
    );
  }

  function value_form(&$form, &$form_state) {
    $start_query = db_select('affiliate_ng_click')
              ->fields('affiliate_ng_click', array('created'))
              ->orderBy('created', 'ASC')
              ->range(0, 1);

    $end_query = db_select('affiliate_ng_click')
              ->fields('affiliate_ng_click', array('created'))
              ->orderBy('created', 'DESC')
              ->range(0, 1);

    /**
     * if we have the UID (for example, if the field is rendered as exposed in the affiliate center),
     * we use it to limit our queries
     */
    if (is_numeric(arg(1))) {
      $start_query->condition('affiliate_uid', arg(1), '=');
      $end_query->condition('affiliate_uid', arg(1), '=');
    }

    $start = $start_query->execute()->fetchField();
    $end = $end_query->execute()->fetchField();

    // no clicks defined
    if (!$start && !$end) {
      $start = $end = REQUEST_TIME;
    }

    // Calculate the years which can be displayed in the form
    $years = range(date('Y', $start), date('Y', $end));
    $form_years = array_combine($years, $years);

    $form['value']['#tree'] = TRUE;

    $form['value']['month'] = array(
      '#type' => 'select',
      '#title' => t('Month'),
      '#options' => array(
        'all' => t('All'),
        '01' => t('January'),
        '02' => t('February'),
        '03' => t('March'),
        '04' => t('April'),
        '05' => t('May'),
        '06' => t('June'),
        '07' => t('July'),
        '08' => t('August'),
        '09' => t('September'),
        '10' => t('October'),
        '11' => t('November'),
        '12' => t('December'),
      ),
      '#default_value' => !empty($this->value['month']) ? $this->value['month'] : date('m'),
      '#multiple' => $this->options['multiple_months'],
    );

    // special case when there's only one option. Just display it, no need for a select box.
    if (count($form_years) == 1) {
      // Pass the value along
      $form['value']['year'] = array(
        '#type' => 'value',
        '#value' => reset($form_years),
      );

      // Display something to the user
      $form['value']['year_display'] = array(
        '#type' => 'item',
        '#title' => t('Year'),
        '#markup' => reset($form_years),
      );
    }
    else {
      $form['value']['year'] = array(
        '#type' => 'select',
        '#title' => t('Year'),
        '#options' => $form_years,
        '#default_value' => !empty($this->value['year']) ? $this->value['year'] : date('Y', $end),
      );
    }
  }

  function query() {
    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";

    // When the option 'multiple_options' is false, we nevertheless
    // force the value to an array, so that we can handle it with the same code
    if (!is_array($this->value['month'])) {
      $this->value['month'] = array($this->value['month'] => $this->value['month']);
    }

    if (in_array('all', $this->value['month'])) {
      $this->query_default();

      return;
    }

    $or = db_or();
    foreach ($this->value['month'] as $month) {
      $start = mktime(0, 0, 0, $month, 1, $this->value['year']);
      $end = mktime(23, 59, 59, $month + 1, 0, $this->value['year']);

      $or->condition($field, array($start, $end), 'BETWEEN');
    }

    $this->query->add_where($this->options['group'], $or);
  }

  /**
   * Makes the query show data for all months of the selected year
   */
  function query_default() {
    $field = "$this->table_alias.$this->real_field";

    $start = mktime(0, 0, 0, 1, 1, $this->value['year']);
    $end = mktime(23, 59, 59, 12, 31, $this->value['year']);

    $this->query->add_where($this->options['group'], $field, array($start, $end), 'BETWEEN');
  }
}