<?php

/**
 * Main class for the commerce_affiliate_commission entity type.
 */
class CommerceAffiliateCommission extends Entity {

  /**
   * The commission type (bundle).
   *
   * @var string
   */
  public $type = NULL;

  /**
   * The uid of the affiliate who received the commission.
   *
   * @var int
   */
  public $affiliate_uid = 0;

  /**
   * The id of the campaign used.
   *
   * @var int
   */
  public $campaign_id = 0;

  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, 'commerce_affiliate_commission');
  }

  public function save() {
    $this->changed = REQUEST_TIME;
    if (!empty($this->is_new) && empty($this->created)) {
      $this->created = REQUEST_TIME;
    }

    parent::save();
  }
}
