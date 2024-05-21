#include <matching_engine.h>

namespace matching_engine {

namespace commands {

std::unique_ptr<Command> Command::from_json(const nlohmann::json &j) {
  auto command_type = static_cast<Command_type>(j.at("type").get<uint8_t>());
  switch (command_type) {
  case Command_type::PLACE_ORDER:
    return Place_order::from_json(j);
  case Command_type::CANCEL_ORDER:
    return Cancel_order::from_json(j);
  case Command_type::DEPOSIT:
    return Deposit::from_json(j);
  case Command_type::PUT_PRODUCT:
    return Put_product::from_json(j);
  default:
    throw std::runtime_error("Unknown CommandType");
  };
}

nlohmann::json Place_order::to_json() const {
  return nlohmann::json{
      {"type", type_}, // TODO Refactor: This way you might forget prepending
                       // the type. Fix other commands too.
      {"productId", product_id_},
      {"orderId", order_id_},
      {"userId", user_id_},
      {"size", size_},
      {"price", price_},
      {"funds", funds_},
      {"orderType", order_type_},
      {"orderSide", order_side_},
      {"time", time_},
  };
}

std::unique_ptr<Place_order> Place_order::from_json(const nlohmann::json &j) {
  auto c = std::make_unique<commands::Place_order>();
  c->product_id_ = j.at("productId").get<std::string>();
  c->order_id_ = j.at("orderId").get<std::string>();
  c->user_id_ = j.at("userId").get<std::string>();
  c->size_ = j.at("size").get<long>();
  c->price_ = j.at("price").get<long>();
  c->funds_ = j.at("funds").get<long>();
  c->order_type_ = j.at("orderType").get<enums::Order_type>();
  c->order_side_ = j.at("orderSide").get<enums::Order_side>();
  c->time_ = j.at("time").get<std::time_t>();

  return c;
}

nlohmann::json Cancel_order::to_json() const {
  return nlohmann::json{
      {"type", type_},
      {"productId", product_id_},
      {"orderId", order_id_},
  };
}

std::unique_ptr<Cancel_order> Cancel_order::from_json(const nlohmann::json &j) {
  auto c = std::make_unique<Cancel_order>();
  c->product_id_ = j.at("productId").get<std::string>();
  c->order_id_ = j.at("orderId").get<std::string>();

  return c;
}

nlohmann::json Put_product::to_json() const {
  return nlohmann::json{
      {"type", type_},
      {"productId", product_id_},
      {"baseCurrency", base_currency_},
      {"quoteCurrency", quote_currency_},
  };
}

std::unique_ptr<Put_product> Put_product::from_json(const nlohmann::json &j) {
  auto c = std::make_unique<Put_product>();
  c->product_id_ = j.at("productId").get<std::string>();
  c->base_currency_ = j.at("baseCurrency").get<std::string>();
  c->quote_currency_ = j.at("quoteCurrency").get<std::string>();

  return c;
}

nlohmann::json Deposit::to_json() const {
  return nlohmann::json{
      {"type", type_},
      {"userId", user_id_},
      {"currency", currency_},
      {"transactionId", tx_id_},
  };
}

std::unique_ptr<Deposit> Deposit::from_json(const nlohmann::json &j) {
  auto c = std::make_unique<Deposit>();
  c->user_id_ = j.at("userId").get<std::string>();
  c->currency_ = j.at("currency").get<std::string>();
  c->tx_id_ = j.at("transactionId").get<std::string>();

  return c;
}

} // namespace commands
} // namespace matching_engine
