
CREATE DATABASE teamphotogenic;
USE teamphotogenic;

CREATE TABLE users (
  user_id BIGINT PRIMARY KEY,

  email VARCHAR(255) UNIQUE,
  phone VARCHAR(255) UNIQUE,

  credits int NOT NULL,
  status int NOT NULL,

  password BINARY(64),
  salt BINARY(16),
  created_at TIMESTAMP NOT NULL,
);
