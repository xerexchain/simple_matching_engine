#pragma once
#include <cstdint>
#include <ctime>
#include <functional>
#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

namespace matching_engine {

namespace errors {

enum class Error_code { INSUFFICIENT_FUNDS };

class Service_exception : public std::runtime_error {
public:
  explicit Service_exception(Error_code code, const std::string &message)
      : std::runtime_error(message), code_(code) {}
  Error_code get_error_code() const noexcept { return code_; }

private:
  Error_code code_;
};

} // namespace errors

namespace enums {

enum class Order_side { BUY, SELL };
enum class Order_type { LIMIT, MARKET };
enum class Order_status { REJECTED, RECEIVED, OPEN, CANCELLED, FILLED };
enum class Time_in_force { GTC, GTT, IOC, FOK };

} // namespace enums

namespace commands {

enum class Command_type : uint8_t { // TODO Remove and use polymorphism
  PLACE_ORDER = 1,
  CANCEL_ORDER,
  DEPOSIT,
  WITHRAWAL,
  PUT_PRODUCT,
};

class Command {
public:
  virtual ~Command() = default;
  virtual nlohmann::json to_json() const = 0;

  static std::unique_ptr<Command> from_json(const nlohmann::json &j);

  long offset_;
  Command_type type_;
};

class Place_order : public Command {
public:
  std::string product_id_, order_id_, user_id_;
  long size_, price_, funds_;
  enums::Order_type order_type_;
  enums::Order_side order_side_;
  std::time_t time_;

  Place_order() noexcept { this->type_ = Command_type::PLACE_ORDER; }
  nlohmann::json to_json() const override;
  static std::unique_ptr<Place_order> from_json(const nlohmann::json &j);
};

class Cancel_order : public Command {
public:
  std::string product_id_, order_id_;

  Cancel_order() noexcept { this->type_ = Command_type::CANCEL_ORDER; }
  nlohmann::json to_json() const override;
  static std::unique_ptr<Cancel_order> from_json(const nlohmann::json &j);
};

class Put_product : public Command {
public:
  std::string product_id_;
  std::string base_currency_, quote_currency_;

  Put_product() noexcept { this->type_ = Command_type::PUT_PRODUCT; }
  nlohmann::json to_json() const override;
  static std::unique_ptr<Put_product> from_json(const nlohmann::json &j);
};

class Deposit : public Command {
public:
  std::string user_id_;
  std::string currency_;
  std::string tx_id_;
  long amount;

  Deposit() noexcept { this->type_ = Command_type::DEPOSIT; }
  nlohmann::json to_json() const override;
  static std::unique_ptr<Deposit> from_json(const nlohmann::json &j);
};
} // namespace commands

// class Order {
// public:
//   Order(const std::string &product_id, const std::string &user_id,
//         const std::string &id, Order_type type, Order_side side, double
//         price, double size, double funds, bool postOnly, std::time_t
//         time);
//   const std::string &get_id() const;
//   Order_side getSide() const;
//   long getPrice() const;
//   long getSize() const;
//   long getRemainingSize() const;
//   long getRemainingFunds() const;
//   std::unique_ptr<Order> clone() const;

// private:
//   std::string id_;
//   std::string user_id_;
//   std::string product_id_;
//   std::string client_order_id_; // TODO oid or order_id
//   Order_type type_;
//   Order_side side_;
//   Order_status status_;
//   long size_; // TODO bigdecimal
//   long price_;
//   long funds_;
//   long remaining_size_;
//   long remaining_funds_;
//   long post_only_;
//   long sequence_;
//   std::time_t time_;
// };
} // namespace matching_engine
