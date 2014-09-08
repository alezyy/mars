<?php

/**
 * Export the affiliate clicks to Views.
 */

/**
 * Implements hook_views_data_alter()
 */
function commerce_affiliate_views_data_alter(&$data) {
  $data['commerce_affiliate_commission']['table']['base']['access query tag'] = 'commerce_affiliate_commission_access';

  $data['commerce_affiliate_commission']['commission_form'] = array(
    'title' => t('Commission form'),
    'help' => t('Display a form for adding new commissions.'),
    'area' => array(
      'handler' => 'commerce_affiliate_handler_area_commission_form',
    ),
  );
  $data['commerce_affiliate_commission']['operations'] = array(
    'title' => t('Operations links'),
    'field' => array(
      'real field' => 'commission_id',
      'help' => t('Display all the available operations links for the commission.'),
      'handler' => 'commerce_affiliate_handler_commission_operations',
    ),
  );
}
