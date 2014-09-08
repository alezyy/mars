<?php
/**
 * @file
 * Rules integration for commissions.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_affiliate_rules_action_info() {
  $actions = array();

  $actions['commerce_affiliate_add_commission'] = array(
    'label' => t('Add commission'),
    'parameter' => array(
      'entity' => array(
        'type' => 'entity',
        'label' => t('Entity to update'),
      ),
      'commission_type' => array(
        'type' => 'text',
        'label' => t('Commission type'),
        'options list' => 'commerce_affiliate_commission_types_options_list'
      ),
      'amount' => array(
        'type' => 'decimal',
        'label' => t('Amount'),
        'description' => 'Amount',
      ),
    ),
    'group' => t('Commerce Affiliate'),
    'callbacks' => array(
      'execute' => 'commerce_affiliate_add_commission',
    ),
  );

  return $actions;
}

function commerce_affiliate_add_commission($entity, $commission_type, $amount) {
  if (is_numeric($amount)) {
    $commission_info = commerce_affiliate_commission_type_load($commission_type);

    $currency_code = commerce_default_currency();

    if ($entity->type() == 'affiliate_click') {
      $account = user_load($entity->value()->affiliate_uid);
    }
    else {
      $account = user_load((int)$_COOKIE['affiliate_ng']['affiliate_uid']);
    }

    // Campaigns.
    if (!empty($_COOKIE['affiliate_ng']['campaign_id'])) {
      $campaign = entity_load_single('affiliate_campaign', $_COOKIE['affiliate_ng']['campaign_id']);
    }
    else {
      $campaign = affiliate_ng_campaign_load_default();
    }

    $values = array(
      'type' => $commission_type,
      'parent_entity_type' => $entity->type(),
      'parent_entity_id' => entity_id($entity->type(), $entity->value()),
      'affiliate_uid' => $account->uid,
      'campaign_id' => $campaign->campaign_id,
    );

    $commission = entity_create('commerce_affiliate_commission', $values);
    $langcode = field_language('commerce_affiliate_commission', $commission, 'commerce_affiliate_amount');

    $commission_wrapper = entity_metadata_wrapper('commerce_affiliate_commission', $commission);
    $commission_wrapper->commerce_affiliate_amount->amount = $amount;
    $commission_wrapper->commerce_affiliate_amount->currency_code = $currency_code;
    entity_save('commerce_affiliate_commission', $commission);
  }
}

function commerce_affiliate_commission_types_options_list() {
  $commission_types = commerce_affiliate_commission_types();
  $options_list = array();
  if ($commission_types) {
    foreach ($commission_types as $commission_type => $value) {
      $options_list[$commission_type] = $value['name'];
    }
  }

  return $options_list;
}