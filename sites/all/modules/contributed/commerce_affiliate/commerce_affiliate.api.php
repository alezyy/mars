<?php

/**
 * @file
 * Hooks provided by the Commerce Affiliate module.
 */

/**
 * Defines commission types that serve as bundles of the commission entity type.
 *
 * When modules are enabled that implement hook_commerce_affiliate_commission_type_info(),
 * Commerce Affiliate will detect it and perform initial configuration of the
 * commission type by adding the locked commerce_affiliate_amount field to the new bundle.
 *
 * @return
 *   An array of commission type info arrays keyed by the type string.
 *   Commission type info arrays are associative arrays containing the following keys:
 *   - type: string containing the machine-name of the commission type; should
 *     only include lowercase letters, numbers, -, and _.
 *   - entity_type: The entity type to which commissions will relate.
 *   - name: the translatable name of the commission type, used in administrative
 *     interfaces including the “Add commission” form.
 *   - description: (Optional) a translatable description, shown in administrative interface.
 *   - admin_ui: (Optional) an array of information used by Commerce Affiliate UI to add
 *     a tab to the entity view page that embeds a view for listing and manipulating commissions
 *     attached to that entity. Only the path key is required (title defaults to "Commissions",
 *     view_name to "commerce_affiliate_commissions", view_display to "master").
 *
 * @see hook_commerce_affiliate_commission_type_info_alter()
 */
function hook_commerce_affiliate_commission_type_info() {
  $commission_types = array();

  $commission_types['user'] = array(
    'type' => 'user',
    'entity_type' => 'user',
    'name' => t('User commission'),
    'description' => t('Awarded to an affiliate after the referred user creates an account.'),
    'admin_ui' => array(
      'title' => t('Commissions'),
      'path' => 'user/%user/commissions',
      'view_name' => 'commerce_affiliate_commissions',
      'view_display' => 'master',
    ),
  );

  return $commission_types;
}

/**
 * Allows modules to alter the commission types info array.
 *
 * @param &$commission_types
 *   An array of commission type info arrays keyed by type.
 */
function hook_commerce_affiliate_commission_type_info_alter(&$commission_types) {
  // No example.
}
