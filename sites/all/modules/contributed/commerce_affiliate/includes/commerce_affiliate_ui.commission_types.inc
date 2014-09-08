<?php

/**
 * @file
 * Defines menu and form callbacks for manipulating commission types.
 */

 /**
  * Menu callback for the commission type tab root.
  * Redirects to the overview page, since there's nothing
  * else to be done.
  */
function commerce_affiliate_ui_commission_type($type) {
  drupal_goto('admin/affiliates/commissions/types');
}

/**
 * Menu callback: display an overview of available types.
 */
function commerce_affiliate_ui_commission_types_overview() {
  drupal_add_css(drupal_get_path('module', 'commerce_affiliate_ui') . '/theme/commerce_affiliate_ui.types.css');

  drupal_set_title(t('Commission types'));

  $header = array(
    t('Name'),
    t('Status'),
    t('Operations'),
  );
  $rows = array();

  // Loop through all defined commission types.
  foreach (commerce_affiliate_commission_types() as $type => $commission_type) {
    // Build the operation links for the current commission type.
    $links = menu_contextual_links('commerce-commission-type', 'admin/affiliates/commissions/types', array(strtr($type, array('_' => '-'))));
    $status = $commission_type['enabled'] ? t('Enabled') : t('Disabled');

    // Add the commission type's row to the table's rows array.
    $rows[] = array(
      theme('commission_type_admin_overview', array('commission_type' => $commission_type)),
      $status,
      theme('links', array('links' => $links, 'attributes' => array('class' => 'links inline operations'))),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Builds an overview of a commission type for display to an administrator.
 *
 * @param $variables
 *   An array of variables used to generate the display; by default includes the
 *     type key with a value of the commission type array.
 *
 * @ingroup themeable
 */
function theme_commission_type_admin_overview($variables) {
  $commission_type = $variables['commission_type'];

  $output = check_plain($commission_type['name']);
  $output .= ' <small> (Machine name: ' . check_plain($commission_type['type']) . ')</small>';
  if (!empty($commission_type['description'])) {
    $output .= '<div class="description">' . filter_xss_admin($commission_type['description']) . '</div>';
  }

  return $output;
}

/**
 * Menu callback: enable a commission type.
 *
 * @see commerce_affiliate_ui_enable_commission_type_form()
 */
function commerce_affiliate_ui_enable_commission_type($type) {
  drupal_set_title(t('Enable a commission type'));

  // Load the full commission type array.
  $commission_type = commerce_affiliate_commission_type_load($type);

  // Add the breadcrumb for the form's location.
  commerce_affiliate_ui_set_breadcrumb(TRUE);

  return drupal_get_form('commerce_affiliate_ui_enable_commission_type_form', $commission_type);
}

/**
 * Menu callback: disable a commission type.
 *
 * @param $type
 *   The machine name of a commission type.
 *
 * @see commerce_affiliate_ui_disable_commission_type_form()
 */
function commerce_affiliate_ui_disable_commission_type($type) {
  drupal_set_title(t('Disable a commission type'));

  // Load the full commission type array.
  $commission_type = commerce_affiliate_commission_type_load($type);

  // Add the breadcrumb for the form's location.
  commerce_affiliate_ui_set_breadcrumb(TRUE);

  return drupal_get_form('commerce_affiliate_ui_disable_commission_type_form', $commission_type);
}

/**
 * Form callback: confirmation form for enabling a commission type.
 *
 * @param $commission_type
 *   The full commission type array.
 */
function commerce_affiliate_ui_enable_commission_type_form($form, $form_state, $commission_type) {
  $form_state['commission_type'] = $commission_type;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_affiliate_commission_ui') . '/includes/commerce_affiliate_ui.commission_types.inc';

  $form = confirm_form($form,
    t('Are you sure you want to enable the %name commission type?', array('%name' => $commission_type['name'])),
    'admin/affiliates/commissions/types',
    '<p>' . t('Please confirm that you want to enable this commission type.') . '</p>',
    t('Enable'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for commerce_affiliate_ui_enable_commission_type_form().
 */
function commerce_affiliate_ui_enable_commission_type_form_submit($form, &$form_state) {
  $commission_type = $form_state['commission_type'];

  $enabled_types = variable_get('commerce_affiliate_ui_enabled_types', _commerce_affiliate_ui_enabled_types_default());
  $enabled_types[$commission_type['type']] = $commission_type['type'];
  variable_set('commerce_affiliate_ui_enabled_types', $enabled_types);

  // Rebuild the menu to update items related to this commission type.
  drupal_static_reset('commerce_affiliate_commission_types');
  menu_rebuild();

  drupal_set_message(t('The commission type %name has been enabled.', array('%name' => $commission_type['name'])));
  $form_state['redirect'] = 'admin/affiliates/commissions/types';
}


/**
 * Form callback: confirmation form for disabling a commission type.
 *
 * @param $commission_type
 *   The full commission type array.
 */
function commerce_affiliate_ui_disable_commission_type_form($form, $form_state, $commission_type) {
  $form_state['commission_type'] = $commission_type;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_affiliate_commission_ui') . '/includes/commerce_affiliate_ui.commission_types.inc';

  $form = confirm_form($form,
    t('Are you sure you want to disable this commission type?'),
    'admin/affiliates/commissions/types',
    t('Are you sure you want to disable the %name commission type?', array('%name' => $commission_type['name'])),
    t('Disable'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for commerce_affiliate_ui_disable_commission_type_form().
 */
function commerce_affiliate_ui_disable_commission_type_form_submit($form, &$form_state) {
  $commission_type = $form_state['commission_type'];

  $enabled_types = variable_get('commerce_affiliate_ui_enabled_types', _commerce_affiliate_ui_enabled_types_default());
  $enabled_types[$commission_type['type']] = FALSE;
  variable_set('commerce_affiliate_ui_enabled_types', $enabled_types);

  // Rebuild the menu to update items related to this commission type
  drupal_static_reset('commerce_affiliate_commission_types');
  menu_rebuild();

  drupal_set_message(t('The commission type %name has been disabled.', array('%name' => $commission_type['name'])));
  $form_state['redirect'] = 'admin/affiliates/commissions/types';
}
