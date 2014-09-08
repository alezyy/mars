<?php

/**
 * Main class for the Affiliate click entity type.
 */
class AffiliateClick extends Entity {
  /**
   * The id of the campaign that this click is attached to.
   *
   * @var int
   */
  public $campaign_id = 0;
  
  /**
   * The uid of the affiliate credited for the click.
   *
   * @var int
   */
  public $affiliate_uid = 0;
  
  /**
   * The IP address that made the click (clicked the affiliate's link).
   *
   * @var string
   */
  public $hostname = '';
  
  /**
   * Referrer.
   * 
   * @var string
   */
  public $referrer = '';
  
  /**
   * Destination (where the user is redirected after the click).
   *
   * @var string
   */
  public $destination = '';
  
  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, 'affiliate_click');
  }
  
  public function save() {
    $this->changed = REQUEST_TIME;
    if (!empty($this->is_new) && empty($this->created)) {
      $this->created = REQUEST_TIME;
    }
    
    parent::save();
  }
}
