<?php

/**
 * @file
 * Provides metadata for the affiliate_campaign and affiliate_click entity types.
 */

/**
 * Implements hook_entity_property_info().
 */
function affiliate_ng_entity_property_info() {
  $info = array();

  // Add meta-data about the basic affiliate_campaign properties.
  $campaign_properties = &$info['affiliate_campaign']['properties'];

  $campaign_properties['campaign_id'] = array(
    'label' => t('Campaign ID'),
    'description' => t('The internal numeric ID of the campaign.'),
    'type' => 'integer',
    'schema field' => 'campaign_id',
  );
  $campaign_properties['name'] = array(
    'label' => t('Name'),
    'description' => t('The name of the campaign.'),
    'type' => 'text',
    'setter callback' => 'entity_metadata_verbatim_set',
    'schema field' => 'name',
    'required' => TRUE,
  );
  $campaign_properties['created'] = array(
    'label' => t('Date created'),
    'description' => t('The date the campaign was created.'),
    'type' => 'date',
    'setter callback' => 'entity_metadata_verbatim_set',
    'schema field' => 'created',
    'required' => TRUE,
  );
  $campaign_properties['default'] = array(
    'label' => t('Default'),
    'type' => 'boolean',
    'description' => t("Whether this is the default campaign (used when no campaign is specified in the URL)."),
    'setter callback' => 'entity_metadata_verbatim_set',
    'schema field' => 'is_default',
  );
  $campaign_properties['active'] = array(
    'label' => t('Active'),
    'type' => 'boolean',
    'description' => t("Whether the campaign is still active (can accept clicks)."),
    'setter callback' => 'entity_metadata_verbatim_set',
    'schema field' => 'is_active',
  );
  $campaign_properties['affiliate_uid'] = array(
    'label' => t('Affiliate UID'),
    'type' => 'integer',
    'description' => t("The UID of the referenced affiliate."),
    'setter callback' => 'entity_metadata_verbatim_set',
    'setter permission' => 'administer affiliates',
    'clear' => array('affiliate'),
    'schema field' => 'affiliate_uid',
  );
  $campaign_properties['affiliate'] = array(
    'label' => t('Affiliate'),
    'type' => 'user',
    'description' => t("The referenced affiliate."),
    'getter callback' => 'affiliate_ng_campaign_get_properties',
    'setter callback' => 'affiliate_ng_campaign_set_properties',
    'setter permission' => 'administer affiliates',
    'clear' => array('affiliate_uid'),
  );

  // Add meta-data about the basic affiliate_click properties.
  $click_properties = &$info['affiliate_click']['properties'];

  $click_properties['click_id'] = array(
    'label' => t('Click ID'),
    'description' => t('The internal numeric ID of the click.'),
    'type' => 'integer',
    'schema field' => 'click_id',
  );
  $click_properties['campaign_id'] = array(
    'label' => t('Campaign ID'),
    'type' => 'integer',
    'description' => t("The ID of the referenced campaign."),
    'setter callback' => 'entity_metadata_verbatim_set',
    'setter permission' => 'administer affiliates',
    'clear' => array('campaign'),
    'schema field' => 'campaign_id',
  );
  $click_properties['campaign'] = array(
    'label' => t('Campaign'),
    'type' => 'affiliate_campaign',
    'description' => t("The referenced campaign."),
    'getter callback' => 'affiliate_ng_click_get_properties',
    'setter callback' => 'affiliate_ng_click_set_properties',
    'setter permission' => 'administer affiliates',
    'clear' => ('campaign_id'),
  );
  $click_properties['hostname'] = array(
    'label' => t('Hostname'),
    'description' => t("The IP address that made the click (clicked the affiliate's link)."),
    'type' => 'text',
    'setter callback' => 'entity_metadata_verbatim_set',
    'schema field' => 'hostname',
  );
  $click_properties['referrer'] = array(
    'label' => t('Referrer'),
    'description' => t('The referring site.'),
    'type' => 'text',
    'setter callback' => 'entity_metadata_verbatim_set',
    'schema field' => 'referrer',
  );
  $click_properties['destination'] = array(
    'label' => t('Destination'),
    'description' => t('The click destination.'),
    'type' => 'text',
    'setter callback' => 'entity_metadata_verbatim_set',
    'schema field' => 'destination',
  );
  $click_properties['created'] = array(
    'label' => t('Date created'),
    'description' => t('The date the click was created.'),
    'type' => 'date',
    'setter callback' => 'entity_metadata_verbatim_set',
    'schema field' => 'created',
  );
  $click_properties['affiliate_uid'] = array(
    'label' => t('Affiliate UID'),
    'type' => 'integer',
    'description' => t("The UID of the referenced affiliate."),
    'setter callback' => 'entity_metadata_verbatim_set',
    'setter permission' => 'administer affiliates',
    'clear' => array('affiliate'),
    'schema field' => 'affiliate_uid',
  );
  $click_properties['affiliate'] = array(
    'label' => t('Affiliate'),
    'type' => 'user',
    'description' => t("The referenced affiliate."),
    'getter callback' => 'affiliate_ng_click_get_properties',
    'setter callback' => 'affiliate_ng_click_set_properties',
    'setter permission' => 'administer affiliates',
    'required' => TRUE,
    'clear' => array('affiliate_uid'),
  );

  return $info;
}
