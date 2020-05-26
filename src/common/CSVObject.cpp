#include "CSVObject.hpp"
#include <utility>

CSVObject::CSVObject(QString value) {
  this->value = std::move(value);
}
/**
 * @brief Gets the internal value as a string
 *
 * @return double
 */
auto CSVObject::asString() -> QString {
  return this->value;
}
/**
 * @brief Gets the internal value as an integer
 *
 * @return double
 */
auto CSVObject::asInt() -> int {
  return this->value.toInt();
}
/**
 * @brief Gets the internal value as a double
 *
 * @return double
 */
auto CSVObject::asDouble() -> double {
  return this->value.toDouble();
}
