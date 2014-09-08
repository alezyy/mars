<?php
/**
 * @file
 * Rules integration for affiliate_ng.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_event_info().
 */
/*
function affiliate_ng_rules_event_info() {
  $events = array();

  $events['affiliate_ng_click'] = array(
    'label' => t('Affiliate click was performed'),
    'group' => t('Affiliate NG'),
    'variables' => array(
      'affiliate_click' => array(
        'type' => 'affiliate_click',
        'label' => t('Affiliate click'),
      ),
    ),
    //'access callback' => 'commerce_order_rules_access',
  );

  return $events;
}
*/
/**
 * Implements hook_rules_condition_info().
 */
function affiliate_ng_rules_condition_info() {
  $conditions = array();
  $conditions['affiliate_ng_is_active_campaign'] = array(
    'label' => t('User has cookie with affiliate_nid and campaign is active.'),
    'group' => t('Affiliate NG'),
    'callbacks' => array(
      'execute' => 'affiliate_ng_is_active_campaign',
    ),
  );

  $conditions['affiliate_ng_check_cookie'] = array(
    'label' => t('Check cookie'),
    'parameter' => array(
      'key' => array(
        'type' => 'text',
        'label' => t('Key'),
        'description' => t('Key in affiliate_ng cookie array'),
      ),
      'value' => array(
        'type' => 'text',
        'label' => t('Value'),
        'description' => t('Value to compare'),
      ),
    ),
    'group' => t('Affiliate NG'),
    'callbacks' => array(
      'execute' => 'affiliate_ng_check_cookie',
    ),
  );
  return $conditions;
}

/**
 * Implements hook_rules_action_info().
 */
function affiliate_ng_rules_action_info() {
  $actions = array();

  $actions['affiliate_ng_set_cookie'] = array(
    'label' => t('Set cookie'),
    'parameter' => array(
      'key' => array(
        'type' => 'text',
        'label' => t('Key'),
        'description' => t('Key in affiliate_ng cookie array'),
      ),
      'value' => array(
        'type' => 'text',
        'label' => t('Value'),
        'description' => t('Value'),
      ),
      'cookie_lifetime' => array(
        'type' => 'text',
        'label' => t('How long should the cookie be valid. Strtotime syntax. The value 0 means "until the browser is closed."'),
        'default value' => variable_get('affiliate_ng_cookie_lifetime', '0'),
      ),
    ),
    'group' => t('Affiliate NG'),
    'callbacks' => array(
      'execute' => 'affiliate_ng_set_cookie',
    ),
  );

  $actions['affiliate_ng_delete_cookie'] = array(
    'label' => t('Delete cookie'),
    'parameter' => array(
      'key' => array(
        'type' => 'text',
        'label' => t('Key'),
        'description' => t('Key in affiliate_ng cookie array'),
      ),
     ),
    'group' => t('Affiliate NG'),
    'callbacks' => array(
      'execute' => 'affiliate_ng_delete_cookie',
    ),
  );

  return $actions;
}
/**
 * Check that cookie exists, affiliate has permission and campaign exists and active.
 */
function affiliate_ng_is_active_campaign() {
  if (!empty($_COOKIE['affiliate_ng']['affiliate_uid'])) {
    $account = user_load((int)$_COOKIE['affiliate_ng']['affiliate_uid']);
    if (!empty($_COOKIE['affiliate_ng']['campaign_id'])) {
      $campaign = entity_load_single('affiliate_campaign', $_COOKIE['affiliate_ng']['campaign_id']);
    } else {
      $campaign = affiliate_ng_campaign_load_default();
    }

    if (user_access('act as an affiliate', $account) && $campaign->is_active) {
      return TRUE;
    }
  }
  
  return FALSE;
}

/**
 * Set cookie
 */
function affiliate_ng_set_cookie($key, $value, $cookie_lifetime) {
  $cookie_lifetime = strtotime($cookie_lifetime);
  setcookie('affiliate_ng[' . $key . ']', $value, $cookie_lifetime, '/');
}

/**
 * Check cookie
 */
function affiliate_ng_check_cookie($key, $value) {
  if (!empty($_COOKIE['affiliate_ng'][$key]) && ($_COOKIE['affiliate_ng'][$key] == $value)) {
    return TRUE;
  }
  return FALSE;
}
/**
 * Deletes cookie
 */
function affiliate_ng_delete_cookie($key) {
  setcookie('affiliate_ng[' . $key . ']', '', time() - 3600, '/');
}