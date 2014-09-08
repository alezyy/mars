<?php

/**
 * @file
 * Defines forms for creating and administering commission commissions.
 */

/**
 * Allows an administrator to choose a commission type and add a commission.
 *
 * @param $parent_entity_type
 *   Limits the commission type selection to types with that entity_type.
 * @param $parent_entity
 *   The parent entity to reference. If empty, a reference widget is shown.
 * @param $commission_type
 *   The machine name of the commission type.
 */
function commerce_affiliate_commission_add_form($form, &$form_state, $parent_entity_type, $parent_entity, $commission_type =  NULL) {
  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_affiliate') . '/includes/commerce_affiliate.forms.inc';

  // Show the form if the user is allowed to create at least one commission type.
  $types = commerce_affiliate_commission_types_get_names($parent_entity_type, TRUE);
  $form['#access'] = FALSE;
  foreach ($types as $type => $name) {
    $commission = entity_create('commerce_affiliate_commission', array('type' => $type));
    if (commerce_affiliate_commission_access('create', $commission)) {
      $form['#access'] = TRUE;
      break;
    }
  }

  if (!isset($commission_type) && !empty($form_state['commission_type'])) {
    $commission_type = $form_state['commission_type'];
  }

  // If a commission method has already been selected...
  if ($commission_type) {
    $values = array(
      'type' => $commission_type,
      'parent_entity_type' => $parent_entity_type,
      'parent_entity_id' => entity_id($parent_entity_type, $parent_entity),
    );
    $form_state['commission'] = entity_create('commerce_affiliate_commission', $values);

    $form['affiliate'] = array(
      '#type' => 'textfield',
      '#title' => t('Affiliate'),
      '#autocomplete_path' => 'user/autocomplete',
      '#maxlength' => '60',
      '#description' => t('The user who received the commission.'),
    );

    $campaigns = affiliate_ng_load_global_campaigns();
    if (count($campaigns) > 1) {
      $options = array();
      foreach ($campaigns as $campaign_id => $campaign) {
        $options[$campaign_id] = $campaign->name;
      }

      $form['campaign_id'] = array(
        '#type' => 'select',
        '#title' => t('Campaign'),
        '#description' => t('Used to differentiate trafic sources.'),
        '#options' => $options,
      );
    }
    else {
      $campaign = reset($campaigns);
      $form['campaign_id'] = array(
        '#type' => 'value',
        '#value' => $campaign->campaign_id,
      );
    }

    // entity_form_field_validate() creates a pseudo-entity out of form state values,
    // so the bundle key (type, in our case) needs to be present.
    $form['type'] = array(
      '#type' => 'value',
      '#value' => $commission_type,
    );

    // Add any available Field API fields.
    field_attach_form('commerce_affiliate_commission', $form_state['commission'], $form, $form_state);

    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
  }
  else {
    $form['#prefix'] = '<div id="commerce-commission-order-commission-add-form">';
    $form['#suffix'] = '</div>';

    $form['commission_type'] = array(
      '#type' => 'select',
      '#options' => $types,
    );
    $form['add_commission'] = array(
      '#type' => 'submit',
      '#value' => t('Add commission'),
      '#ajax' => array(
        'callback' => 'commerce_affiliate_commission_add_form_add_refresh',
        'wrapper' => 'commerce-commission-order-commission-add-form',
      ),
    );
  }

  return $form;
}

/**
 * Returns the full commission form when a commission type is selected.
 */
function commerce_affiliate_commission_add_form_add_refresh($form, $form_state) {
  return $form;
}

/**
 * Validation callback for commerce_affiliate_commission_add_form().
 */
function commerce_affiliate_commission_add_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] != t('Add commission')) {
    $commission_type = $form_state['commission_type'];
    $parent_entity = $form_state['build_info']['args'][1];

    $exists = (bool) db_query_range('SELECT 1 FROM {users} WHERE name = :name', 0, 1, array(':name' => $form_state['values']['affiliate']))->fetchField();
    if (!$exists) {
      form_set_error('affiliate', t('Enter a valid username.'));
    }

    entity_form_field_validate('commerce_affiliate_commission', $form, $form_state);
  }
}

/**
 * Submit callback for commerce_affiliate_commission_add_form().
 */
function commerce_affiliate_commission_add_form_submit($form, &$form_state) {
  // If the "Add commission" button was clicked...
  if ($form_state['values']['op'] == t('Add commission')) {
    // Store the commission type in the form state and rebuild the form.
    $form_state['commission_type'] = $form_state['values']['commission_type'];
    $form_state['rebuild'] = TRUE;
  }
  else {
    $affiliate_uid = db_query('SELECT uid from {users} WHERE name = :name', array(':name' => $form_state['values']['affiliate']))->fetchField();
    $commission = $form_state['commission'];
    $commission->affiliate_uid = $affiliate_uid;

    // Merge the form state values (properties, fields) into the entity.
    entity_form_submit_build_entity('commerce_affiliate_commission', $commission, $form, $form_state);

    entity_save('commerce_affiliate_commission', $commission);

    drupal_set_message(t('Commission created.'));
  }
}

/**
 * Form callback: confirmation form for deleting a commission.
 *
 * @param $commission
 *   The commission commission object to be deleted.
 *
 * @see confirm_form()
 */
function commerce_affiliate_commission_delete_form($form, &$form_state, $order, $commission) {
  $form_state['order'] = $order;
  $form_state['commission'] = $commission;

  // Load and store the commission method.
  $commission_type = commerce_affiliate_method_load($commission->commission_type);
  $form_state['commission_type'] = $commission_type;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_affiliate') . '/includes/commerce_affiliate.commission.inc';

  $form = confirm_form($form,
    t('Are you sure you want to delete this commission?'),
    '',
    '<p>' . t('@amount paid via %method on @date. Deleting this commission cannot be undone.', array('@amount' => commerce_currency_format($commission->amount, $commission->currency_code), '%method' => $commission_type['title'], '@date' => format_date($commission->created, 'short'))) . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for commerce_affiliate_commission_delete_form().
 */
function commerce_affiliate_commission_delete_form_submit($form, &$form_state) {
  $commission = $form_state['commission'];

  entity_delete('commerce_affiliate_commission', $commission->commission_id);
  drupal_set_message(t('Commission deleted.'));
  watchdog('commerce_affiliate', 'Deleted commission @commission.', array('@commission' => $commission->commission_id), WATCHDOG_NOTICE);
}
