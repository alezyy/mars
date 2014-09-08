<?php

/**
 * @file
 * Provides the UI for viewing, creating, updating, and deleting campaigns, both from the
 * admin pages and the affiliate center.
 */

/** 
 * Page callback: view a campaign.
 */
function affiliate_ng_ui_campaign_view($campaign, $account) {
  $view = entity_view('affiliate_campaign', array($campaign->campaign_id => $campaign));
  $output = '<div>' . t('Referral link') . '</div>';
  $output .= '<div>'. t('Front page') . ': http://' . $_SERVER['HTTP_HOST'] . '/ref/' . $account->uid . '/' . $campaign->campaign_id . '</div>';
  $output .= '<div>'. t('Custom page') . ': http://' . $_SERVER['HTTP_HOST'] . '/custom_page?a=' . $account->uid . '&c=' . $campaign->campaign_id . '</div>';
  $output .= drupal_render($view);
  return $output;
}

/**
 * Form callback wrapper: create or edit a campaign.
 *
 * @param $campaign The campaign entity, if an edit action is happening.
 * @param $account  Affiliate user object. NULL if the campaign is being added
 *                  by the admin (in which case the campaign is global and has
 *                  no assigned affiliate)
 *
 * @see affiliate_ng_campaign_form()
 */
function affiliate_ng_campaign_form_wrapper($campaign = NULL, $account = NULL) {
  // Add the breadcrumb for the form's location.
  affiliate_ng_ui_campaign_set_breadcrumb($account);
  
  // Initialize a campaign if this is an add action.
  if (!$campaign) {
    $campaign = entity_create('affiliate_campaign', array());
  }

  return drupal_get_form('affiliate_ng_campaign_form', $campaign, $account);
}

/**
 * Form callback: create or edit an affiliate campaign.
 * Used both by affiliates (from their Affiliate Center) and by admins
 * (to create global campaigns), in which case the $account object is NULL.
 *
 * @param $form
 * @param $form_state
 * @param $campaign The campaign entity, if an edit action is happening.
 * @param $account  Affiliate user object. NULL if the campaign is being added
 *                  by the admin (in which case the campaign is global and has
 *                  no assigned affiliate)
 */
function affiliate_ng_campaign_form($form, &$form_state, $campaign, $account = NULL) {
  $form_state['campaign'] = $campaign;
  $form_state['account'] = $account;
  $form_state['redirect'] = _affiliate_ng_ui_campaign_get_redirect_url($account, $form_state);

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $campaign->name,
    '#description' => t('Displayed in the statistics pages to identify the campaign.'),
    '#required' => TRUE,
  );

  // Give other modules a chance to add some fields to the form.
  field_attach_form('affiliate_campaign', $campaign, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#weight' => 1000,
    '#attributes' => array('class' => array('form-actions')),
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  if (!empty($campaign->is_new)) {
    drupal_set_title(t('Add a campaign'));
    
    $form['actions']['save_continue'] = array(
      '#type' => 'submit',
      '#value' => t('Save and add another'),
      '#suffix' => l('Cancel', $form_state['redirect']),
      '#weight' => 45,
    );
  }
  else {
    $form['actions']['submit']['#suffix'] = l('Cancel', $form_state['redirect']);
  }

  return $form;
}

/**
 * Form submit handler: save the campaign.
 */
function affiliate_ng_campaign_form_submit($form, &$form_state) {
  $campaign = $form_state['campaign'];
  $account = $form_state['account'];

  $campaign->name = $form_state['values']['name'];
  $campaign->affiliate_uid = isset($account) ? $account->uid : 0;
  // Notify field widgets.
  field_attach_submit('affiliate_campaign', $campaign, $form, $form_state);

  $campaign->save();
  drupal_set_message(t('Your campaign has been saved.'));
}

/**
 * Form callback wrapper: delete a campaign.
 *
 * @param $campaign The campaign entity, if an edit action is happening.
 * @param $account  Affiliate user object. NULL if the campaign is being deleted from 
 *                  the admin pages.
 *
 * @see affiliate_ng_campaign_form()
 */
function affiliate_ng_campaign_delete_form_wrapper($campaign , $account = NULL) {
  // Add the breadcrumb for the form's location.
  affiliate_ng_ui_campaign_set_breadcrumb($account);

  return drupal_get_form('affiliate_ng_campaign_delete_form', $campaign, $account);
}

/**
 * Confirmation form for deleting an affiliate campaign.
 */
function affiliate_ng_campaign_delete_form($form, &$form_state, $campaign, $account = NULL) {
  $form_state['campaign'] = $campaign;
  $form_state['account'] = $account;

  $form = confirm_form($form,
    t('Are you sure you want to delete the %name campaign?', array('%name' => $campaign->name)),
    _affiliate_ng_ui_campaign_get_redirect_url($account, $form_state),
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Form submit handler: delete the campaign.
 */
function affiliate_ng_campaign_delete_form_submit($form, &$form_state) {
  $campaign = $form_state['campaign'];
  $account = $form_state['account'];

  $campaign->delete();

  drupal_set_message(t('The campaign %name has been deleted.', array('%name' => $campaign->name)));
  watchdog('affiliate_ng', 'Deleted campaign %name.', array('%name' => $campaign->name), WATCHDOG_NOTICE);
  $form_state['redirect'] = _affiliate_ng_ui_campaign_get_redirect_url($account, $form_state);
}

/**
 * Returns the proper redirect URL.
 *
 * If the provided $account object is empty, this means the admin is adding
 * global campaigns.
 * If the $account object is not empty, the affiliate is adding campaigns
 * from his own campaign pages.
 *
 * Additionally, the redirect varies based on the button clicked
 * (redirect back to the list, or to the form itself).
 */
function _affiliate_ng_ui_campaign_get_redirect_url($account, $form_state) {
  if (!isset($account)) {
    $url = 'admin/affiliates/campaigns';
  }
  else {
    $url = 'user/' . $account->uid . '/affiliate/campaigns';
  }
  
  if (isset($form_state['clicked_button']) && $form_state['clicked_button']['#parents'][0] == 'save_continue') {
    $url .= '/add';
  }
  
  return $url;
}

/**
 * Sets the breadcrumb for campaign forms.
 */
function affiliate_ng_ui_campaign_set_breadcrumb($account) {
  if (!isset($account)) {
    $breadcrumb = array(
      l(t('Home'), '<front>'),
      l(t('Administration'), 'admin'),
      l(t('Affiliates'), 'admin/affiliates'),
      l(t('Campaigns'), 'admin/affiliates/campaigns'),
    );
  }
  else {
    $breadcrumb = array(
      l(t('Home'), '<front>'),
      l($account->name, 'user/' . $account->uid),
      l(t('Affiliate Center'), 'user/' . $account->uid . '/affiliate'),
      l(t('Campaigns'), 'user/' . $account->uid . '/affiliate/campaigns'),
    );
  }
  
  drupal_set_breadcrumb($breadcrumb);
}

