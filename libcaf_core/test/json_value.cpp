// This file is part of CAF, the C++ Actor Framework. See the file LICENSE in
// the main distribution directory for license terms and copyright or visit
// https://github.com/actor-framework/actor-framework/blob/master/LICENSE.

#define CAF_SUITE json_value

#include "caf/json_value.hpp"

#include "core-test.hpp"

#include "caf/binary_deserializer.hpp"
#include "caf/binary_serializer.hpp"
#include "caf/json_array.hpp"
#include "caf/json_object.hpp"

using namespace caf;
using namespace std::literals;

TEST_CASE("default-constructed") {
  auto val = json_value{};
  CHECK(val.is_null());
  CHECK(!val.is_undefined());
  CHECK(!val.is_integer());
  CHECK(!val.is_integer());
  CHECK(!val.is_double());
  CHECK(!val.is_number());
  CHECK(!val.is_bool());
  CHECK(!val.is_string());
  CHECK(!val.is_array());
  CHECK(!val.is_object());
  CHECK_EQ(val.to_integer(), 0);
  CHECK_EQ(val.to_double(), 0.0);
  CHECK_EQ(val.to_bool(), false);
  CHECK_EQ(val.to_string(), ""sv);
  CHECK_EQ(val.to_object().size(), 0u);
  CHECK_EQ(deep_copy(val), val);
}

TEST_CASE("from undefined") {
  auto val = json_value::undefined();
  CHECK(!val.is_null());
  CHECK(val.is_undefined());
  CHECK(!val.is_integer());
  CHECK(!val.is_integer());
  CHECK(!val.is_double());
  CHECK(!val.is_number());
  CHECK(!val.is_bool());
  CHECK(!val.is_string());
  CHECK(!val.is_array());
  CHECK(!val.is_object());
  CHECK_EQ(val.to_integer(), 0);
  CHECK_EQ(val.to_double(), 0.0);
  CHECK_EQ(val.to_bool(), false);
  CHECK_EQ(val.to_string(), ""sv);
  CHECK_EQ(val.to_object().size(), 0u);
  CHECK_EQ(deep_copy(val), val);
}

TEST_CASE("from integer") {
  auto val = unbox(json_value::parse("42"));
  CHECK(!val.is_null());
  CHECK(!val.is_undefined());
  CHECK(val.is_integer());
  CHECK(!val.is_double());
  CHECK(val.is_number());
  CHECK(!val.is_bool());
  CHECK(!val.is_string());
  CHECK(!val.is_array());
  CHECK(!val.is_object());
  CHECK_EQ(val.to_integer(), 42);
  CHECK_EQ(val.to_double(), 42.0);
  CHECK_EQ(val.to_bool(), false);
  CHECK_EQ(val.to_string(), ""sv);
  CHECK_EQ(val.to_object().size(), 0u);
  CHECK_EQ(deep_copy(val), val);
}

TEST_CASE("from double") {
  auto val = unbox(json_value::parse("42.0"));
  CHECK(!val.is_null());
  CHECK(!val.is_undefined());
  CHECK(!val.is_integer());
  CHECK(val.is_double());
  CHECK(val.is_number());
  CHECK(!val.is_bool());
  CHECK(!val.is_string());
  CHECK(!val.is_array());
  CHECK(!val.is_object());
  CHECK_EQ(val.to_integer(), 42);
  CHECK_EQ(val.to_double(), 42.0);
  CHECK_EQ(val.to_bool(), false);
  CHECK_EQ(val.to_string(), ""sv);
  CHECK_EQ(val.to_object().size(), 0u);
  CHECK_EQ(deep_copy(val), val);
}

TEST_CASE("from bool") {
  auto val = unbox(json_value::parse("true"));
  CHECK(!val.is_null());
  CHECK(!val.is_undefined());
  CHECK(!val.is_integer());
  CHECK(!val.is_double());
  CHECK(!val.is_number());
  CHECK(val.is_bool());
  CHECK(!val.is_string());
  CHECK(!val.is_array());
  CHECK(!val.is_object());
  CHECK_EQ(val.to_integer(), 0);
  CHECK_EQ(val.to_double(), 0.0);
  CHECK_EQ(val.to_bool(), true);
  CHECK_EQ(val.to_string(), ""sv);
  CHECK_EQ(val.to_object().size(), 0u);
  MESSAGE(deep_to_string(val));
  CHECK_EQ(deep_copy(val), val);
}

TEST_CASE("from string") {
  auto val = unbox(json_value::parse(R"_("Hello, world!")_"));
  CHECK(!val.is_null());
  CHECK(!val.is_undefined());
  CHECK(!val.is_integer());
  CHECK(!val.is_double());
  CHECK(!val.is_number());
  CHECK(!val.is_bool());
  CHECK(val.is_string());
  CHECK(!val.is_array());
  CHECK(!val.is_object());
  CHECK_EQ(val.to_integer(), 0);
  CHECK_EQ(val.to_double(), 0.0);
  CHECK_EQ(val.to_bool(), false);
  CHECK_EQ(val.to_string(), "Hello, world!"sv);
  CHECK_EQ(val.to_object().size(), 0u);
  CHECK_EQ(deep_copy(val), val);
}

TEST_CASE("from empty array") {
  auto val = unbox(json_value::parse("[]"));
  CHECK(!val.is_null());
  CHECK(!val.is_undefined());
  CHECK(!val.is_integer());
  CHECK(!val.is_double());
  CHECK(!val.is_number());
  CHECK(!val.is_bool());
  CHECK(!val.is_string());
  CHECK(val.is_array());
  CHECK(!val.is_object());
  CHECK_EQ(val.to_integer(), 0);
  CHECK_EQ(val.to_double(), 0.0);
  CHECK_EQ(val.to_bool(), false);
  CHECK_EQ(val.to_string(), ""sv);
  CHECK_EQ(val.to_array().size(), 0u);
  CHECK_EQ(val.to_object().size(), 0u);
  CHECK_EQ(deep_copy(val), val);
}

TEST_CASE("from non-empty array") {
  auto val = unbox(json_value::parse("[1, 2, 3]"));
  CHECK(!val.is_null());
  CHECK(!val.is_undefined());
  CHECK(!val.is_integer());
  CHECK(!val.is_double());
  CHECK(!val.is_number());
  CHECK(!val.is_bool());
  CHECK(!val.is_string());
  CHECK(val.is_array());
  CHECK(!val.is_object());
  CHECK_EQ(val.to_integer(), 0);
  CHECK_EQ(val.to_double(), 0.0);
  CHECK_EQ(val.to_bool(), false);
  CHECK_EQ(val.to_string(), ""sv);
  CHECK_EQ(val.to_array().size(), 3u);
  CHECK_EQ(val.to_object().size(), 0u);
  CHECK_EQ(deep_copy(val), val);
}

TEST_CASE("from empty object") {
  auto val = unbox(json_value::parse("{}"));
  CHECK(!val.is_null());
  CHECK(!val.is_undefined());
  CHECK(!val.is_integer());
  CHECK(!val.is_double());
  CHECK(!val.is_number());
  CHECK(!val.is_bool());
  CHECK(!val.is_string());
  CHECK(!val.is_array());
  CHECK(val.is_object());
  CHECK_EQ(val.to_integer(), 0);
  CHECK_EQ(val.to_double(), 0.0);
  CHECK_EQ(val.to_bool(), false);
  CHECK_EQ(val.to_string(), ""sv);
  CHECK_EQ(val.to_object().size(), 0u);
  CHECK_EQ(deep_copy(val), val);
}

TEST_CASE("from non-empty object") {
  auto val = unbox(json_value::parse(R"_({"foo": "bar"})_"));
  CHECK(!val.is_null());
  CHECK(!val.is_undefined());
  CHECK(!val.is_integer());
  CHECK(!val.is_double());
  CHECK(!val.is_number());
  CHECK(!val.is_bool());
  CHECK(!val.is_string());
  CHECK(!val.is_array());
  CHECK(val.is_object());
  CHECK_EQ(val.to_integer(), 0);
  CHECK_EQ(val.to_double(), 0.0);
  CHECK_EQ(val.to_bool(), false);
  CHECK_EQ(val.to_string(), ""sv);
  CHECK_EQ(val.to_object().size(), 1u);
  CHECK_EQ(deep_copy(val), val);
}
