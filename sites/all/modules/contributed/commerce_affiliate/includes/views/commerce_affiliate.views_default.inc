<?php

/**
 * Implements hook_views_default_views().
 */
function commerce_affiliate_views_default_views() {
  $views = array();

  $view = new view;
  $view->name = 'commerce_affiliate_commissions';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_affiliate_commission';
  $view->human_name = 'Commerce Affiliate Commissions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'created' => 'created',
    'name_1' => 'name_1',
    'name' => 'name',
    'commerce_affiliate_amount' => 'commerce_affiliate_amount',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'commerce_affiliate_amount' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Footer: Affiliate Commission: Commission form */
  $handler->display->display_options['footer']['commission_form']['id'] = 'commission_form';
  $handler->display->display_options['footer']['commission_form']['table'] = 'commerce_affiliate_commission';
  $handler->display->display_options['footer']['commission_form']['field'] = 'commission_form';
  $handler->display->display_options['footer']['commission_form']['label'] = 'commission_form';
  $handler->display->display_options['footer']['commission_form']['empty'] = FALSE;
  /* Relationship: Affiliate Commission: Affiliate affiliate_uid */
  $handler->display->display_options['relationships']['affiliate']['id'] = 'affiliate';
  $handler->display->display_options['relationships']['affiliate']['table'] = 'commerce_affiliate_commission';
  $handler->display->display_options['relationships']['affiliate']['field'] = 'affiliate';
  $handler->display->display_options['relationships']['affiliate']['required'] = 1;
  /* Relationship: Affiliate Commission: Campaign campaign_id */
  $handler->display->display_options['relationships']['campaign']['id'] = 'campaign';
  $handler->display->display_options['relationships']['campaign']['table'] = 'commerce_affiliate_commission';
  $handler->display->display_options['relationships']['campaign']['field'] = 'campaign';
  $handler->display->display_options['relationships']['campaign']['required'] = 0;
  /* Field: Affiliate Commission: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_affiliate_commission';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'users';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'affiliate';
  $handler->display->display_options['fields']['name_1']['label'] = 'Affiliate';
  $handler->display->display_options['fields']['name_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name_1']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name_1']['overwrite_anonymous'] = 0;
  $handler->display->display_options['fields']['name_1']['format_username'] = 1;
  /* Field: Affiliate campaign: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'affiliate_ng_campaign';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'campaign';
  $handler->display->display_options['fields']['name']['label'] = 'Campaign';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  /* Field: Affiliate Commission: Amount */
  $handler->display->display_options['fields']['commerce_affiliate_amount']['id'] = 'commerce_affiliate_amount';
  $handler->display->display_options['fields']['commerce_affiliate_amount']['table'] = 'field_data_commerce_affiliate_amount';
  $handler->display->display_options['fields']['commerce_affiliate_amount']['field'] = 'commerce_affiliate_amount';
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['commerce_affiliate_amount']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_affiliate_amount']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_affiliate_amount']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_affiliate_amount']['field_api_classes'] = 0;
  /* Field: Affiliate Commission: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'commerce_affiliate_commission';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['label'] = 'Operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;
  $handler->display->display_options['fields']['operations']['hide_alter_empty'] = 1;
  /* Sort criterion: Affiliate Commission: Date created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'commerce_affiliate_commission';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Contextual filter: Affiliate Commission: Parent entity id */
  $handler->display->display_options['arguments']['parent_entity_id']['id'] = 'parent_entity_id';
  $handler->display->display_options['arguments']['parent_entity_id']['table'] = 'commerce_affiliate_commission';
  $handler->display->display_options['arguments']['parent_entity_id']['field'] = 'parent_entity_id';
  $handler->display->display_options['arguments']['parent_entity_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['parent_entity_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['parent_entity_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['parent_entity_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['parent_entity_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['parent_entity_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['parent_entity_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['parent_entity_id']['not'] = 0;
  /* Contextual filter: Affiliate Commission: Parent entity type */
  $handler->display->display_options['arguments']['parent_entity_type']['id'] = 'parent_entity_type';
  $handler->display->display_options['arguments']['parent_entity_type']['table'] = 'commerce_affiliate_commission';
  $handler->display->display_options['arguments']['parent_entity_type']['field'] = 'parent_entity_type';
  $handler->display->display_options['arguments']['parent_entity_type']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['parent_entity_type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['parent_entity_type']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['parent_entity_type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['parent_entity_type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['parent_entity_type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['parent_entity_type']['glossary'] = 0;
  $handler->display->display_options['arguments']['parent_entity_type']['limit'] = '0';
  $handler->display->display_options['arguments']['parent_entity_type']['transform_dash'] = 0;
  $handler->display->display_options['arguments']['parent_entity_type']['break_phrase'] = 0;
  $views[$view->name] = $view;

  return $views;
}
