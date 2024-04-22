


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


