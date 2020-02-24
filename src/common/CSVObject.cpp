#include "CSVObject.h"

CSVObject::CSVObject(QString value) {
  this->value = value;
}
/**
 * @brief Gets the internal value as a string
 *
 * @return double
 */
QString CSVObject::asString() {
  return this->value;
}
/**
 * @brief Gets the internal value as an integer
 *
 * @return double
 */
int CSVObject::asInt() {
  return this->value.toInt();
}
/**
 * @brief Gets the internal value as a double
 *
 * @return double
 */
double CSVObject::asDouble() {
  return this->value.toDouble();
}
