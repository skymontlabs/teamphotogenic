Create table MusicPlaylist
(
    SongId int,
    SongName text,
    Year int,
    Singer text,
    Primary key(SongId, SongName)
);

Create table task_to_images
(

);

Create table user_to_tasks
(
    Student_rollno int,
    user_id bigint,
    task_id bigint,
);

Create table user_to_images
(
    Student_rollno int,
    user_id bigint,
    task_id bigint,
);
