<?php

/**
 * Export the affiliate clicks to Views.
 */

/**
 * Implements hook_views_data_alter()
 */
function affiliate_ng_views_data_alter(&$data) {
  $data['affiliate_ng_campaign']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'real field' => 'campaign_id',
      'additional fields' => array('affiliate_uid', 'is_default'),
      'help' => t('Display all the available operations links for the campaign.'),
      'handler' => 'affiliate_ng_handler_field_campaign_operations',
    ),
  );
  $data['affiliate_ng_campaign']['name'] = array(
    'field' => array(
      'title' => t('Campaign name'),
      'real field' => 'campaign_id',
      'additional fields' => array('name'),
      'help' => t('Display campaign name and link on it.'),
      'handler' => 'affiliate_ng_handler_field_campaign_name',
    ),
  );
  $data['affiliate_ng_click']['affiliate_uid'] = array(
    'argument' => array(
      'handler' => 'affiliate_ng_handler_argument_campaign',
    ),
  );
  $data['affiliate_ng_click']['created'] = array(
    'filter' => array(
      'handler' => 'affiliate_ng_handler_filter_date',
    ),
  );
}

/**
 * Implements hook_views_plugins().
 */
function affiliate_ng_views_plugins() {
  return array(
    'access' => array(
      'affiliate_ng_dashboard_access' => array(
        'title' => t('Affiliate Center'),
        'handler' => 'affiliate_ng_plugin_dashboard_access',
        'uses options' => FALSE,
      ),
    ),
  );
}