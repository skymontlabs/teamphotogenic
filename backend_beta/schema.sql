CREATE KEYSPACE tpg WITH replication = {
  'class': 'SimpleStrategy',
  'replication_factor': '1'
};

USE tpg;

CREATE TABLE users (
  user_id bigint PRIMARY KEY,
  email text,
  phone text,

  credits int,
  
  # password [64 byte password + 16 byte seed]
  pwd blob,

  # totp [10 byte secret + 4 byte timestamp]
  #totp blob,

  # preferences
  preferences bigint,
  prms int,
  
  ---pref_gender tinyint,
  ---pref_age_group tinyint,

  # this user's demographics
  ---gender tinyint,
  ---age_grp tinyint,
  ---habits tinyint,
  ---language tinyint,
);
CREATE INDEX ON users (email);
CREATE INDEX ON users (phone);
CREATE INDEX ON users (username);

---
---create_user
---insert into users(user_id,email,phone,credits,pwd,totp,pref) values()

---register_user
---same as above

---get_seed
---select prms,pwd,totp,pref from users where email= and phone=

---submit_code(login)
---insert into recent

---submit_password(login)
---same as above

---submit_totp(login)
---same as above

---read_user
---select email,phone,totp_unix,gender,age_grp,habits,language 

---read_users
---select user_id,email,phone,permissions,gender,age_grp

---update_user
---update users set

---delete_user
---update users set

---logout
---

---read_notifications
---
# login
# 

CREATE TABLE experiments (
  experiment_id bigint PRIMARY KEY,
  user_id bigint,
  title text,

  total_elos int,
  total_likerts int,
  total_pts int,

  total_images int,

  status tinyint,
);
CREATE INDEX ON experiments (user_id);

---create_experiment
---INSERT INTO experiments (experiment_id,title,total_elos,total_likerts,total_pts,total_images,status) 
---VALUES ();

---read_experiments
---insert into experiments values()

---read_experiment_id
---select * from experiments where experiment_id=
---select * from images where experiment_id=uuid_here;

---update_experiment
---update experiments set title= where

---delete_experiment
---delete from experiments where experiment_id=


CREATE TABLE images (
  image_id bigint PRIMARY KEY,
  
  experiment_id bigint,
  series_id tinyint,
  
  user_id bigint,

  total_elos int,
  total_likerts int, --- sum score

  elo_wins int,
  elo_score int,
  likert_raw_sum int, --- sum score
  likert_adj_sum int, --- adj score
);

CREATE INDEX ON images (experiment_id);
CREATE INDEX ON images (series_id);
CREATE INDEX ON images (user_id);
CREATE INDEX ON images (tags);



---read image
---select * from images where image_id = uuid_here;
---select * from elo_ratings where image_id = uuid_here;
---select * from likert_ratings where image_id = uuid_here;

---update_experiment
---update experiments set title='tit' where experiment_id=EID

---delete_image
---delete from images where experiment_id=EID
---update experiments set continuous=0 where experiment_id=EID


CREATE TABLE skipped??? (
  elo_id bigint PRIMARY KEY,

  winner_elo int,
  loser_elo int,

  number_comparisons int,
);


CREATE TABLE elo_ratings (
  elo_id bigint PRIMARY KEY,
  experiment_id bigint,
  image_id bigint,
  user_id bigint,

  winner_idx tinyint,
  loser_idx tinyint,
  winner_elo int,
  loser_elo int,

  number_comparisons int,
);
CREATE TABLE likert_scores (
  likert_id bigint PRIMARY KEY,
  experiment_id bigint,
  image_id bigint,
  user_id bigint,

  score int,
  tag int,
  comment text,
);

CREATE INDEX ON elo_ratings (experiment_id);
CREATE INDEX ON elo_ratings (winner_idx);
CREATE INDEX ON elo_ratings (loser_idx);







CREATE TABLE likert_scores (
  likert_id bigint PRIMARY KEY,
  experiment_id bigint,
  image_id bigint,
  user_id bigint,

  score int,
  tag int,
  comment text,
  PRIMARY KEY (image_id, user_id)
);
CREATE INDEX ON likert_scores (score);

--- create rating




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


