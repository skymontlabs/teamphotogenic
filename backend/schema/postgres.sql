
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




