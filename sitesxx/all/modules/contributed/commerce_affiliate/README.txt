Commerce Affiliate is a part of the Affiliate-NG (http://drupal.org/project/affiliate_ng) module suite.

Affiliate-NG provides the basic affiliate functionality:
- Affiliate URL handling
- Clicks (recorded visits based on affiliate referrals)
- Campaigns (ways to differentiate traffic sources)
- Reports for administrators ("Affiliates" page) and
  users ("Affiliate Center" tab on the user profile).

Commerce Affiliate extends that functionality by allowing
affiliates to earn commissions (relying on Commerce for price and
currency handling).
A commission is an entity referencing a parent entity (for which
the affiliate received the commission), usually created by Rules
(as a response to an Order being completed, a refered user creating an
account, etc) or by the admin, through the UI.
There can be multiple commission types, each specifying the entity
type of the parent entity, and allowing additional fields to be attached.

Once a commission type for a certain entity type has been added
(by implementing hook_commerce_affiliate_commission_type_info(), or through the UI)
a new tab called "Commissions" appears on the entity view page, allowing you
to see existing commissions, delete them, or add new ones.
So if a commission type "Node commissions" gets created, for awarding users
for creating nodes, going to node/2/commissions would allow you to see the
commissions awarded for that specific node.

Included in the package is the "Commerce Affiliate Order" submodule,
which provides commission types, views, rules and other functionality
for commerce_order commissions.
This allows per-order and per-product commissioning functionality out of the box.

Please note that these modules are not yet production-ready.
Their primary audience are developers, looking to develop flexible
affiliating solutions for their clients, ready to tweak Views
and apply additional polish.

TODO:
- Payments
- Better access control
- Better UI

Use the isssue queue (http://drupal.org/project/issues/commerce_affiliate) to report
problems, suggest documentation or UI improvements, or just say thanks.