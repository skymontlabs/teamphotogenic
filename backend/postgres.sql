CREATE DATABASE tpgn;

USE tpgn;

CREATE TABLE users (
  user_id BIGINT PRIMARY KEY,

  email VARCHAR(255),
  phone VARCHAR(255),

  credits int not null,
  status int not null,

  # password [64 byte password + 16 byte seed]
  password_hash BINARY(80),
  created_at TIMESTAMP not null
);
CREATE INDEX idx_users_email ON users (email);
CREATE INDEX idx_users_phone ON users (phone);


DELIMITER $$

CREATE PROCEDURE cuser(
    IN p_email VARCHAR(255),
    IN p_phone VARCHAR(255),
    IN p_credits INT,
    IN p_password_hash BINARY(80)
)
BEGIN
    INSERT INTO users (email, phone, credits, password_hash, created_at)
    VALUES (p_email, p_phone, p_credits, p_password_hash, CURRENT_TIMESTAMP);
END $$

CREATE PROCEDURE guser(
    IN p_user_id BIGINT
)
BEGIN
    SELECT * FROM users WHERE user_id = p_user_id;
END $$


CREATE PROCEDURE geuser(
    IN p_email VARCHAR(255)
)
BEGIN
    SELECT * FROM users WHERE email = p_email;
END $$


CREATE PROCEDURE gpuser(
    IN p_phone VARCHAR(255)
)
BEGIN
    SELECT * FROM users WHERE phone = p_phone;
END $$

CREATE PROCEDURE ucredits(
    IN p_user_id BIGINT,
    IN p_credits INT
)
BEGIN
    UPDATE users
    SET credits = p_credits
    WHERE user_id = p_user_id;
END $$

CREATE PROCEDURE uuser(
    IN p_user_id BIGINT,
    IN p_email VARCHAR(255),
    IN p_phone VARCHAR(255),
    IN p_credits INT,
    IN p_password_hash BINARY(80)
)
BEGIN
    UPDATE users
    SET email = p_email, 
        phone = p_phone,
        credits = p_credits,
        password_hash = p_password_hash
    WHERE user_id = p_user_id;
END $$


CREATE PROCEDURE duser(
    IN p_user_id BIGINT
)
BEGIN
    DELETE FROM users WHERE user_id = p_user_id;
END $$

DELIMITER ;








CREATE TABLE image_sets (
  image_set_id BIGINT PRIMARY KEY,
  user_id BIGINT,

  title CHAR(32),

  total_elos INT,
  total_likerts INT,
  total_pts INT,

  total_images INT,

  status TINYINT,

  created_at TIMESTAMP,
  FOREIGN KEY (user_id) REFERENCES users(user_id)
);
CREATE INDEX idx_imagesets_user_id ON image_sets (email);

DELIMITER $$

CREATE PROCEDURE CreateImageSet(
    IN p_user_id BIGINT,
    IN p_title CHAR(32),
    IN p_total_elos INT,
    IN p_total_likerts INT,
    IN p_total_pts INT,
    IN p_total_images INT,
    IN p_status TINYINT
)
BEGIN
    INSERT INTO image_sets (user_id, title, total_elos, total_likerts, total_pts, total_images, status, created_at)
    VALUES (p_user_id, p_title, p_total_elos, p_total_likerts, p_total_pts, p_total_images, p_status, CURRENT_TIMESTAMP);
END $$


CREATE PROCEDURE GetImageSet(
    IN p_image_set_id BIGINT
)
BEGIN
    SELECT * FROM image_sets WHERE image_set_id = p_image_set_id;
END $$

CREATE PROCEDURE GetImageSetsByUser(
    IN p_user_id BIGINT
)
BEGIN
    SELECT * FROM image_sets WHERE user_id = p_user_id;
END $$


CREATE PROCEDURE DeleteImageSet(
    IN p_image_set_id BIGINT
)
BEGIN
    DELETE FROM image_sets WHERE image_set_id = p_image_set_id;
END $$

DELIMITER ;




CREATE TABLE images (
  image_id BIGINT PRIMARY KEY,
  imageset_id BIGINT,
  url TEXT,

  series_id tinyint,
  
  user_id bigint,

  total_elos int,
  total_likerts int, --- sum score

  elo_wins int,
  elo_score int,
  likert_raw_sum int, --- sum score
  likert_adj_sum int, --- adj score

  upload_time TIMESTAMP,
  FOREIGN KEY (imageset_id) REFERENCES image_sets(imageset_id)
);

DELIMITER $$

CREATE PROCEDURE GetImage(
    IN p_image_id BIGINT
)
BEGIN
    SELECT * FROM images WHERE image_id = p_image_id;
END $$


CREATE PROCEDURE DeleteImage(
    IN p_image_id BIGINT
)
BEGIN
    DELETE FROM images WHERE image_id = p_image_id;
END $$

DELIMITER ;






CREATE TABLE ratings (
  rating_id BIGINT PRIMARY KEY,
  imageset_id BIGINT,
  image_id BIGINT,

  rater_user_id BIGINT,
  rating_type TINYINT,
  rating_value INT,
  rating_time TIMESTAMP,

  FOREIGN KEY (image_id) REFERENCES images(image_id),
  FOREIGN KEY (rater_user_id) REFERENCES users(user_id)
);


CREATE TABLE elo_ratings (
  elo_id bigint PRIMARY KEY,
  imageset_id bigint,
  image_id bigint,
  user_id bigint,

  winner_idx tinyint,
  loser_idx tinyint,
  winner_elo int,
  loser_elo int,

  number_comparisons int,
);




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


