
CREATE TABLE users (
  user_id BIGINT PRIMARY KEY,

  email VARCHAR(255),
  phone VARCHAR(255),

  credits int not null,

  # password [64 byte password + 16 byte seed]
  password_hash BINARY(80),
  created_at TIMESTAMP not null
);

CREATE INDEX idx_users_email ON users (email);
CREATE INDEX idx_users_phone ON users (phone);


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




CREATE TABLE ratings (
  rating_id BIGINT PRIMARY KEY,
  image_id BIGINT,
  rater_user_id BIGINT,
  rating_type TINYINT,
  rating_value INT,
  rating_time TIMESTAMP,

  FOREIGN KEY (image_id) REFERENCES images(image_id),
  FOREIGN KEY (rater_user_id) REFERENCES users(user_id)
);




CREATE TABLE elo_scores (
  score_id BIGINT PRIMARY KEY,
  image_id BIGINT,
  elo_score INT,
  
  FOREIGN KEY (image_id) REFERENCES images(image_id)
);



