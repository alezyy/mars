<?php

/**
 * @file
 * Defines menu callbacks for manipulating commissions.
 */

/**
 * Menu callback: delete a commission from the admin pages.
 *
 * @param $commission
 *   The commission entity.
 *
 * @see commerce_affiliate_delete_commission_form()
 */
function commerce_affiliate_ui_commission_admin_delete($commission) {
  drupal_set_title(t('Delete commission'));

  // Add the breadcrumb for the form's location.
  //commerce_affiliate_ui_set_breadcrumb(TRUE);

  module_load_include('inc', 'commerce_affiliate', 'includes/commerce_affiliate.forms');
  return drupal_get_form('commerce_affiliate_delete_commission_form', $commission);
}

/**
 * Menu callback: show a list of commissions for the passed parent entity.
 * The list is shown by embedding a view, which has an add form
 * in its footer.
 *
 * @param $parent_entity
 *   The parent entity for which commissions are loaded.
 * @param $type
 *   The machine name of the commission type.
 */
function commerce_affiliate_ui_commission_list($parent_entity, $type) {
  // Load the full commission type array.
  $commission_type = commerce_affiliate_commission_type_load($type);

  $view_name = $commission_type['admin_ui']['view_name'];
  $view_display = $commission_type['admin_ui']['view_display'];
  $parent_entity_id = entity_id($commission_type['entity_type'], $parent_entity);
  $arguments = array($parent_entity_id, $commission_type['entity_type'], $commission_type['type']);

  $output = commerce_embed_view($view_name, $view_display, $arguments);
  return array('#markup' => $output);
}

/**
 * Menu callback: delete a commission from the commission UI.
 *
 * @param $commission_id
 *   The id of the commission to view.
 *
 * @see commerce_affiliate_delete_commission_form()
 */
function commerce_affiliate_ui_commission_delete($commission_id) {
  drupal_set_title(t('Delete commission'));

  // Load the commission. Return a 404 if it can't be loaded.
  $commission = entity_load_single('commerce_affiliate_commission', $commission_id);
  if (!$commission) {
    return MENU_NOT_FOUND;
  }

  // Add the breadcrumb for the form's location.
  commerce_affiliate_ui_set_breadcrumb(TRUE);

  module_load_include('inc', 'commerce_affiliate', 'includes/commerce_affiliate.forms');
  return drupal_get_form('commerce_affiliate_delete_commission_form', $commission);
}
/**
 * Ask for confirmation of commission deletion
 */
function commerce_affiliate_delete_commission_form($form, &$form_state, $commission) {
  $form = array();
  $form['#commission'] = $commission;
  $form['commission_id'] = array('#type' => 'value', '#value' => $commission->commission_id);
  // @todo change redirect.
  return confirm_form($form,
    t('Are you sure you want to delete commission?'),
    '<front>',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
  return $form;
}
/**
 * Execute commission deletion
 */
function commerce_affiliate_delete_commission_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $commission = $form['#commission'];
    commerce_affiliate_delete($form_state['values']['commission_id']);
    watchdog('commission', 'Commission @type has been deleted.', array('@type' => $commission->type));
    drupal_set_message(t('Commission @type has been deleted.', array('@type' => $commission->type)));
  }
  // @todo change redirect.
  $form_state['redirect'] = '<front>';
}