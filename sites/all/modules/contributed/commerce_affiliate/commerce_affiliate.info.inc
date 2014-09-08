<?php

/**
 * @file
 * Provides metadata for the commission entity.
 */

/**
 * Implements hook_entity_property_info().
 */
function commerce_affiliate_entity_property_info() {
  $info = array();

  $properties = &$info['commerce_affiliate_commission']['properties'];

  $properties['commission_id'] = array(
    'label' => t('Commission ID'),
    'description' => t('The internal numeric ID of the commission.'),
    'type' => 'integer',
    'schema field' => 'commission_id',
  );
  $properties['type'] = array(
    'label' => t('Type'),
    'description' => t('The commission type.'),
    'type' => 'token',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commissions',
    'options list' => 'commerce_affiliate_commission_type_options_list',
    'required' => TRUE,
    'schema field' => 'type',
  );
  $properties['affiliate'] = array(
    'label' => t('Affiliate'),
    'type' => 'user',
    'description' => t('The user who received the commission.'),
    'getter callback' => 'commerce_affiliate_get_properties',
    'setter callback' => 'commerce_affiliate_set_properties',
    'setter permission' => 'administer commissions',
    'required' => TRUE,
    'schema field' => 'affiliate_uid',
  );
  $properties['campaign'] = array(
    'label' => t('Campaign'),
    'type' => 'affiliate_campaign',
    'description' => t('The campaign used.'),
    'getter callback' => 'commerce_affiliate_get_properties',
    'setter callback' => 'commerce_affiliate_set_properties',
    'setter permission' => 'administer commissions',
    'required' => TRUE,
    'schema field' => 'campaign_id',
  );
  $properties['parent_entity_id'] = array(
    'label' => t('Parent entity id'),
    'description' => t('The id of the parent entity for which the affiliate received a commission.'),
    'type' => 'integer',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commissions',
    'required' => TRUE,
    'schema field' => 'parent_entity_id',
  );
  $properties['parent_entity_type'] = array(
    'label' => t('Parent entity type'),
    'description' => t('The type of the parent entity for which the affiliate received a commission.'),
    'type' => 'token',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commissions',
    'options list' => 'commerce_affiliate_entity_type_list',
    'required' => TRUE,
    'schema field' => 'parent_entity_type',
  );
  $properties['created'] = array(
    'label' => t('Date created'),
    'description' => t('The date the commission was created.'),
    'type' => 'date',
    'setter callback' => 'entity_metadata_verbatim_set',
    'setter permission' => 'administer commissions',
    'schema field' => 'created',
  );
  $properties['changed'] = array(
    'label' => t('Date changed'),
    'description' => t('The date the commission was most recently updated.'),
    'type' => 'date',
    'schema field' => 'changed',
  );

  return $info;
}

/**
 * Implements hook_entity_property_info_alter().
 *
 * Hacky way to provide tokens for the fields this module
 * creates on its entity.
 */
function commerce_affiliate_entity_property_info_alter(&$info) {
  if (!empty($info['commerce_affiliate_commission']['bundles'])) {
    $properties = array();

    foreach ($info['commerce_affiliate_commission']['bundles'] as $bundle => $bundle_info) {
      $bundle_info += array('properties' => array());
      $properties += $bundle_info['properties'];
    }

    $properties['commerce_affiliate_amount']['description'] = t('The amount that the affiliate earned for the commission.');
    $info['commerce_affiliate_commission']['properties']['commerce_affiliate_amount'] = $properties['commerce_affiliate_amount'];
  }
}
