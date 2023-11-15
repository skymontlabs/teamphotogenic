CREATE KEYSPACE tpg WITH replication = {
  'class': 'SimpleStrategy',
  'replication_factor': '1'
};

USE tpg;

CREATE TABLE users (
  user_id bigint PRIMARY KEY,
  email text,
  phone text,
  username text,
  totp_secret blob,
  hashed_password blob,
  created_at timestamp,
  last_login timestamp
);
CREATE INDEX ON users (email);
CREATE INDEX ON users (phone);
CREATE INDEX ON users (username);

CREATE TABLE experiments (
  experiment_id bigint PRIMARY KEY,
  user_id bigint,
  title text,
  description text,
  created_at timestamp,
  updated_at timestamp
);
CREATE INDEX ON experiments (user_id);

CREATE TABLE images (
  image_id bigint PRIMARY KEY,
  experiment_id bigint,
  series_id tinyint,
  user_id bigint,
  image blob,
  tags int, -- Storing tags as a bitmask
);
CREATE INDEX ON images (experiment_id);
CREATE INDEX ON images (user_id);
CREATE INDEX ON images (tags);

CREATE TABLE image_elo_scores (
  feedback_id bigint PRIMARY KEY,
  image_id bigint,
  user_id bigint,
  comment text,
  created_at timestamp

  image_id bigint PRIMARY KEY,
  elo_score int,
  number_comparisons int
);
CREATE INDEX ON image_elo_scores (elo_score);

CREATE TABLE image_likert_scores (
  image_id bigint,
  user_id bigint,
  score int,
  PRIMARY KEY (image_id, user_id)
);
CREATE INDEX ON image_likert_scores (score);

-- For user sessions, to manage active logins and possibly for websocket connections
CREATE TABLE user_sessions (
  session_id bigint PRIMARY KEY,
  user_id bigint,
  created_at timestamp,
  last_accessed timestamp,
  client_info text
);
CREATE INDEX ON user_sessions (user_id);

-- 
CREATE TABLE surveys (
  survey_id bigint PRIMARY KEY,
  question text,
  created_at timestamp
);

-- Survey Multiple Choice List
CREATE TABLE survey_choicelist (
  survey_id bigint PRIMARY KEY,
  question text,
  created_at timestamp
);

-- 
CREATE TABLE survey_responses (
  survey_id bigint PRIMARY KEY,
  question text,
  created_at timestamp
);


