<?php

/**
 * @file
 * Contains the code used by commerce_coffee_coffee_command().
 */

/**
 * Switchboard. Returns specific command array.
 */
function commerce_coffee_get_commands($op) {
  $command = strstr($op, ' ', TRUE);
  $param = drupal_substr($op, (drupal_strlen($command)) + 1, drupal_strlen($op));
  switch ($command) {
    case 'u':
      return _commerce_coffee_getuser($param);
      break;

    case 'sku':
      return _commerce_coffee_getsku($param);
      break;

    case 'o':
      return _commerce_coffee_getorder($param);
  }
}

/**
 * Retrieve link for a given user, either by name or email.
 *
 * @param string $param
 * The parameter to use for search.
 */
function _commerce_coffee_getuser($param) {
  $email = $param;
  $return = array();
  if (!empty($email)) {
    if ($s_user = user_load_by_mail($email) or $s_user = user_load_by_name($email)) {
      $return[] = array(
        'path' => 'user/' . $s_user->uid,
        'title' => t('View @user\'s user page', array('@user' => $s_user->name)),
      );

      // Let's see if we can get the latest order...
      $query = new EntityFieldQuery();

      $query
          ->entityCondition('entity_type', 'commerce_order', '=')
          ->entityOrderBy('entity_id', 'DESC')
          ->range(0, 1)
          ->propertyCondition('uid', $s_user->uid, '=');
      $result = $query->execute();
      foreach ($result['commerce_order'] as $order_id => $order) {
        $order = commerce_order_load($order_id);
        $return[] = array(
          'path' => 'admin/commerce/orders/' . $order_id,
          t("Order @id dated @date", array('@id' => $order_id, '@date' => format_date($order->created, 'custom', 'd-m-Y'))),
        );
      }
    }
  }
  return $return;
}

/**
 * Retrieve products & displays for a given SKU.
 *
 * @param string $param
 * The parameter to use for search.
 */
function _commerce_coffee_getsku($sku) {
  $return = array();
  if (!empty($sku)) {
    if ($product = commerce_product_load_by_sku((string) $sku)) {
      $return[] = array(
        'path' => 'admin/commerce/products/' . $product->product_id,
        'title' => t("Product -> @title", array('@title' => $product->title)),
      );
      // If we found a product, we can try to find product displays.
      $product_display_types = _commerce_coffee_get_product_display_types(FALSE);
      if (!empty($product_display_types)) {
        // Get all product reference fields
        $product_fields = _commerce_coffee_get_product_reference_fields();
        $nodes_query = db_select('node', 'n');
        $field_conditions = db_and();
        foreach ($product_fields as $field_name) {
          $nodes_query->join('field_data_' . $field_name, 'fd_' . $field_name, 'fd_' . $field_name . '.entity_id = n.nid');
          $nodes_query->join('commerce_product', 'cp_' . $field_name, 'cp_' . $field_name . '.product_id = fd_' . $field_name . '.' . $field_name . '_product_id');
          $nodes_query->fields('cp_' . $field_name, array('type', 'product_id', 'sku', 'title', 'language'));
          $field_conditions->condition('cp_' . $field_name . "." . "sku", $sku, "=");
        }
        $nodes_query->fields('n', array('nid', 'title' => 'title', 'language', 'type'));
        $nodes_query->orderBy('n.title');
        $nodes_query->addTag('node_access');
        $conditions = db_or();
        foreach ($product_display_types as $product_display_type) {
          $conditions->condition('n.type', $product_display_type['machine_name']);
        }
        if ($conditions->count()) {
          $nodes_query->condition($conditions);
        }
        $nodes_query->condition($field_conditions);

        $nodes_query_result = $nodes_query->execute();

        foreach ($nodes_query_result as $record) {
          $return[] = array(
            'path' => 'node/' . $record->nid,
            'title' => t('Display -> @display', array('@display' => $record->n_title)),
          );
        }
      }
    }
  }

  return $return;
}

/**
 * Retrieve a specific order ID.
 *
 * @param string $order_id
 * The parameter to use for search.
 */
function _commerce_coffee_getorder($order_id) { {
    $return = array();
    if (is_numeric($order_id)) {

      // Let's see if we can get the latest order...
      $query = new EntityFieldQuery();

      $query
          ->entityCondition('entity_type', 'commerce_order', '=')
          ->entityOrderBy('entity_id', 'DESC')
          ->range(0, 1)
          ->propertyCondition('order_id', $order_id, '=');
      $result = $query->execute();

      foreach ($result['commerce_order'] as $order_id => $order) {
        $order = commerce_order_load($order_id);
        $return[] = array(
          'path' => 'admin/commerce/orders/' . $order_id,
          'title' =>
          t("Show order @id dated @date", array('@id' => $order_id, '@date' => format_date($order->created, 'custom', 'd-m-Y'))),
        );
        $return[] = array(
          'path' => 'admin/commerce/orders/' . $order_id . "/edit",
          'title' => t("Edit order @id dated @date", array('@id' => $order_id, '@date' => format_date($order->created, 'custom', 'd-m-Y'))),
        );
      }
    }
  }
  return $return;
}

function _commerce_coffee_get_product_display_types() {
  $entities = array();
  foreach (field_info_fields() as $field) {
    if ($field['type'] == 'commerce_product_reference' && !empty($field['bundles']['node'])) {
      foreach ($field['bundles']['node'] as $bundle) {
        $entities[] = array(
          'machine_name' => $bundle,
          'name' => node_type_get_name($bundle)
        );
      }
    }
  }
  return $entities;
}

/**
 * Return all product reference fields in the drupal installation.
 */
function _commerce_coffee_get_product_reference_fields() {
  $product_reference_fields = array();
  foreach (field_info_fields() as $field) {
    // Do not include the commerce_product field, why?
    if ($field['type'] == 'commerce_product_reference' && $field['field_name'] != 'commerce_product') {
      $product_reference_fields[] = $field['field_name'];
    }
  }
  return $product_reference_fields;
}
