
/*
INSERT INTO mytable (id, a, b, c)
VALUES (1, 'a1', 'b1', 'c1'),
(2, 'a2', 'b2', 'c2'),
(3, 'a3', 'b3', 'c3'),
(4, 'a4', 'b4', 'c4'),
(5, 'a5', 'b5', 'c5'),
(6, 'a6', 'b6', 'c6')
ON DUPLICATE KEY UPDATE id=VALUES(id),
a=VALUES(a),
b=VALUES(b),
c=VALUES(c);


INSERT INTO tabelname(id, col2, col3, col4)
VALUES
    (1, 1, 1, 'text for col4'),
    (DEFAULT,1,4,'another text for col4')
ON CONFLICT (id) DO UPDATE SET
    col2 = EXCLUDED.col2,
    col3 = EXCLUDED.col3,
    col4 = EXCLUDED.col4
*/
CREATE DATABASE teamphotogenic;
USE teamphotogenic;

CREATE TABLE users (
  user_id BIGINT PRIMARY KEY,

  email VARCHAR(255) UNIQUE,
  phone VARCHAR(255) UNIQUE,

  credits int NOT NULL,
  status int NOT NULL,

  password BINARY(96),
  created_at TIMESTAMP NOT NULL,
);

DELIMITER $$
CREATE PROCEDURE cuser(
    IN p_email VARCHAR(255),
    IN p_phone VARCHAR(255),
    IN p_credits INT,
    IN p_password_hash BINARY(80),
    IN p_created TIMESTAMP,
)
BEGIN
    INSERT INTO users (email, phone, credits, password_hash, created_at)
    VALUES (p_email, p_phone, p_credits, p_password_hash, p_created);
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

CREATE PROCEDURE acredits(
    IN p_user_id BIGINT,
    IN p_credits INT
)
BEGIN
    UPDATE users
    SET credits = credits + p_credits
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


CREATE PROCEDURE CPWD(
    IN p_password BINARY(96),
)
BEGIN
    UPDATE users
    SET password = p_password
    WHERE user_id = p_user_id;
END $$

CREATE PROCEDURE duser(
    IN p_user_id BIGINT
)
BEGIN
    UPDATE users SET status=2 WHERE user_id = p_user_id;
END $$
DELIMITER ;








CREATE TABLE image_sets (
  image_set_id BIGINT PRIMARY KEY,
  user_id BIGINT NOT NULL,
  title CHAR(32) NOT NULL,

  total_elos INT NOT NULL DEFAULT 0,
  total_likerts INT NOT NULL DEFAULT 0,
  total_pts INT NOT NULL DEFAULT 0,

  target_elos INT NOT NULL,
  target_likerts INT NOT NULL,
  target_pts INT NOT NULL,

  total_images INT NOT NULL DEFAULT 0,

  status TINYINT NOT NULL DEFAULT 0,

  created_at TIMESTAMP NOT NULL,
  FOREIGN KEY (user_id) REFERENCES users(user_id)
);
CREATE INDEX idx_image_sets_user_id ON image_sets (user_id);
CREATE INDEX idx_image_sets_title ON image_sets (title);
CREATE INDEX idx_image_sets_total_elos ON image_sets (total_elos);
CREATE INDEX idx_image_sets_total_likerts ON image_sets (total_likerts);
CREATE INDEX idx_image_sets_total_pts ON image_sets (total_pts);
CREATE INDEX idx_image_sets_target_elos ON image_sets (target_elos);
CREATE INDEX idx_image_sets_target_likerts ON image_sets (target_likerts);
CREATE INDEX idx_image_sets_target_pts ON image_sets (target_pts);
CREATE INDEX idx_image_sets_total_images ON image_sets (total_images);
CREATE INDEX idx_image_sets_status ON image_sets (status);
CREATE INDEX idx_image_sets_created_at ON image_sets (created_at);


CREATE INDEX idx_image_sets_title_user ON image_sets (title, user_id);
CREATE INDEX idx_image_sets_total_elos_user ON image_sets (total_elos, user_id);
CREATE INDEX idx_image_sets_total_likerts_user ON image_sets (total_likerts, user_id);
CREATE INDEX idx_image_sets_total_pts_user ON image_sets (total_pts, user_id);
CREATE INDEX idx_image_sets_target_elos_user ON image_sets (target_elos, user_id);
CREATE INDEX idx_image_sets_target_likerts_user ON image_sets (target_likerts, user_id);
CREATE INDEX idx_image_sets_target_pts_user ON image_sets (target_pts, user_id);
CREATE INDEX idx_image_sets_total_images_user ON image_sets (total_images, user_id);
CREATE INDEX idx_image_sets_created_at_user ON image_sets (created_at, user_id);


DELIMITER $$
CREATE PROCEDURE cimageset(
    IN p_user_id BIGINT,
    IN p_title CHAR(32),
    IN p_total_elos INT,
    IN p_total_likerts INT,
    IN p_total_pts INT,
    IN p_total_images INT,
    IN p_created TINYINT
)
BEGIN
    INSERT INTO image_sets (user_id, title, total_elos, total_likerts, total_pts, total_images, created_at)
    VALUES (p_user_id, p_title, p_total_elos, p_total_likerts, p_total_pts, p_total_images, p_created);
END $$

CREATE PROCEDURE gimageset(
    IN p_image_set_id BIGINT
)
BEGIN
    SELECT * FROM image_sets WHERE image_set_id = p_image_set_id;
END $$

CREATE PROCEDURE giuimageset(
    IN p_image_set_id BIGINT,
    IN p_user_id BIGINT
)
BEGIN
    SELECT * FROM image_sets WHERE image_set_id = p_image_set_id AND user_id = p_user_id;
END $$

CREATE PROCEDURE guimageset(
    IN p_user_id BIGINT
)
BEGIN
    SELECT * FROM image_sets WHERE user_id = p_user_id;
END $$

DELIMITER ;




CREATE TABLE images (
  image_id BIGINT PRIMARY KEY,
  imageset_id BIGINT,
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

CREATE INDEX idx_images_imageset_id ON images (imageset_id);
CREATE INDEX idx_images_series_id ON images (series_id);
CREATE INDEX idx_images_user_id ON images (user_id);
CREATE INDEX idx_images_total_likerts ON images (total_likerts);
CREATE INDEX idx_images_likert_raw_sum ON images (likert_raw_sum);
CREATE INDEX idx_images_likert_adj_sum ON images (likert_adj_sum);

CREATE INDEX idx_images_imageset_id_user_id ON images (imageset_id, user_id);
CREATE INDEX idx_images_series_id_user_id ON images (series_id, user_id);
CREATE INDEX idx_images_total_elos_user_id ON images (total_elos, user_id);
CREATE INDEX idx_images_total_likerts_user_id ON images (total_likerts, user_id);
CREATE INDEX idx_images_elo_wins_user_id ON images (elo_wins, user_id);
CREATE INDEX idx_images_elo_score_user_id ON images (elo_score, user_id);
CREATE INDEX idx_images_likert_raw_sum_user_id ON images (likert_raw_sum, user_id);
CREATE INDEX idx_images_likert_adj_sum_user_id ON images (likert_adj_sum, user_id);
CREATE INDEX idx_images_upload_time_user_id ON images (upload_time, user_id);




DELIMITER $$
CREATE PROCEDURE gimage(
    IN p_image_id BIGINT
)
BEGIN
    SELECT * FROM images WHERE image_id = p_image_id;
END $$

CREATE PROCEDURE dimage(
    IN p_image_id BIGINT
)
BEGIN
    DELETE FROM images WHERE image_id = p_image_id;
END $$

CREATE PROCEDURE dimageset(
    IN p_image_set_id BIGINT
)
BEGIN
    DELETE FROM image_sets WHERE image_set_id = p_image_set_id;
    DELETE FROM image_sets WHERE image_set_id = p_image_set_id;
END $$
DELIMITER ;





CREATE TABLE likert_ratings (
  likert_id BIGINT PRIMARY KEY,
  imageset_id BIGINT,
  image_id BIGINT,

  rater_user_id BIGINT,
  rating_value INT,
  rating_time TIMESTAMP,

  FOREIGN KEY (image_id) REFERENCES images(image_id),
  FOREIGN KEY (rater_user_id) REFERENCES users(user_id)
);

CREATE INDEX idx_likert_imageset_id ON likert_ratings (imageset_id);
CREATE INDEX idx_likert_image_id ON likert_ratings (image_id);
CREATE INDEX idx_likert_rater_user_id ON likert_ratings (rater_user_id);
CREATE INDEX idx_likert_rating_value ON likert_ratings (rating_value);
CREATE INDEX idx_likert_rating_time ON likert_ratings (rating_time);
CREATE INDEX idx_likert_image_rating ON likert_ratings (image_id, rating_value);
CREATE INDEX idx_likert_image_imageset ON likert_ratings (image_id, imageset_id);

CREATE INDEX idx_likert_imageset_rater ON likert_ratings (imageset_id, rater_user_id);


DELIMITER $$
CREATE PROCEDURE glikerts_user(
    IN p_rater_user_id BIGINT
)
BEGIN
    SELECT * FROM likert_ratings
    WHERE rater_user_id = p_rater_user_id;
END $$

CREATE PROCEDURE glikerts_img(
    IN p_imageset_id BIGINT,
    IN p_image_id BIGINT
)
BEGIN
    SELECT * FROM likert_ratings
    WHERE imageset_id = p_imageset_id
    AND image_id = p_image_id;
END $$

CREATE PROCEDURE glikerts_user_imgset(
    IN p_rater_user_id BIGINT,
    IN p_imageset_id BIGINT
)
BEGIN
    SELECT * FROM likert_ratings
    WHERE rater_user_id = p_rater_user_id
    AND imageset_id = p_imageset_id;
END $$

CREATE PROCEDURE glikerts_grp(
    IN p_rater_user_id BIGINT,
    IN p_imageset_id BIGINT
)
BEGIN
    SELECT rating_value, COUNT(*) AS count
    FROM likert_ratings
    WHERE rater_user_id = p_rater_user_id
    AND imageset_id = p_imageset_id
    GROUP BY rating_value;
END $$

CREATE PROCEDURE glikerts_imgset(
    IN p_imageset_id BIGINT
)
BEGIN
    SELECT * FROM likert_ratings
    WHERE imageset_id = p_imageset_id;
END $$
DELIMITER ;



CREATE TABLE elo_ratings (
  elo_id BIGINT PRIMARY KEY,
  imageset_id BIGINT,
  rater_user_id BIGINT,
  recv_user_id BIGINT,

  winner_idx TINYINT,
  loser_idx TINYINT,
  winner_elo INT,
  loser_elo INT,
  rating_time TIMESTAMP,

  ---number_comparisons INT,

  FOREIGN KEY (image_id) REFERENCES images(image_id),
  FOREIGN KEY (rater_user_id) REFERENCES users(user_id)
  FOREIGN KEY (recv_user_id) REFERENCES users(user_id)
);

CREATE INDEX idx_elo_winner_loser ON elo_ratings (imageset_id, winner_idx, loser_idx);
CREATE INDEX idx_elo_imageset_id_rater_user_id ON elo_ratings (imageset_id, rater_user_id);
CREATE INDEX idx_elo_imageset_id_recv_user_id ON elo_ratings (imageset_id, recv_user_id);


DELIMITER $$

CREATE PROCEDURE celo(
    IN p_imageset_id BIGINT,
    IN p_rater_user_id BIGINT,
    IN p_winner_idx TINYINT,
    IN p_loser_idx TINYINT,
    IN p_winner_elo INT,
    IN p_loser_elo INT
)
BEGIN
    INSERT INTO elo_ratings (imageset_id, rater_user_id, winner_idx, loser_idx, winner_elo, loser_elo, rating_time)
    VALUES (p_imageset_id, p_rater_user_id, p_winner_idx, p_loser_idx, p_winner_elo, p_loser_elo, CURRENT_TIMESTAMP);
END $$


CREATE PROCEDURE FindEloRatingsByImageSetIdAndIndex(
    IN p_imageset_id BIGINT,
    IN p_idx TINYINT
)
BEGIN
    SELECT * FROM elo_ratings
    WHERE imageset_id = p_imageset_id AND (winner_idx = p_idx OR loser_idx = p_idx);
END $$




CREATE PROCEDURE delo(
    IN p_elo_id BIGINT
)
BEGIN
    DELETE FROM elo_ratings WHERE elo_id = p_elo_id;
END $$

DELIMITER ;








-- For user sessions, to manage active logins and possibly for websocket connections
CREATE TABLE user_sessions (
  session_id BIGINT PRIMARY KEY,
  user_id BIGINT,
  created_at TIMESTAMP,
  last_accessed TIMESTAMP,
  client_info TEXT,

  FOREIGN KEY (user_id) REFERENCES users(user_id)
);
CREATE INDEX idx_sess_created_at ON user_sessions (user_id);
CREATE INDEX idx_sess_created_at ON user_sessions (created_at);

DELIMITER $$
CREATE PROCEDURE mrsession(
    IN p_user_id BIGINT
)
BEGIN
    SELECT * FROM user_sessions
    WHERE user_id = p_user_id
    ORDER BY created_at DESC
    LIMIT 3;
END $$
DELIMITER ;



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


