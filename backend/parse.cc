enum actions
{
    GET_SEED                 = 0x01,
    LOGIN,
    SIGNUP,
    SUBMIT_TOTP,
    INIT_CHANGE_PASSWORD,
    CHANGE_PASSWORD,
    VERIFY_ACCT,
    INIT_TOTP,
    ADD_TOTP,
    REMOVE_TOTP,

    GET_TASKS,
    GET_TASKID,
    RATE_INDIV,
    RATE_PAIRS,
    CREATE_TASK,
    DELETE_TASK,
    ACTIVATE_TASK,
    STOP_TASK,
    GET_USER
};

void get_seed(uint8_t* out, const char* email, size_t length)
{
    // if not present at all, then randomly generate
    if (bloom_filter(email, length)) {
        random(out, 16);
        seed_cache.set(email, length, out);
        return;
    }

    // must look at database
    if (dbi.get(out, email, length) == 0) {
        random(out, 16);
        seed_cache.set(email, length, out);
        return;
    }

}

int login()
{
    if (bloom_filter(email, length)) {
        return -1;
    }

    if (dbi.login(email, length, password)) {
        // generate key
        return 0;
    }

    return -1;
}

void signup()
{
    //
    if (bloom_filter()) {

    }

    return dbi.signup();
}

void submit_totp()
{

}

void init_change_password()
{
    let oldSeed = ArrayBuffer(msg, 1)
    let newSeed = ArrayBuffer(msg, 1)

    changePassword(contact, oldPassword, newPassword, oldSeed, newSeed)
}

void change_password()
{

}

void change_acct()
{

}

void verify_acct()
{

}

void init_totp()
{
    
}

void add_totp(uint64_t user_id, uint64_t totp)
{
    totp_cache.get();
}

void remove_totp(uint64_t user_id)
{
    dbi.remove_totp(user_id);
}


void get_tasks()
{
    dbi.get_tasks(user_id)
}

void get_task_id(uint64_t task_id, userdata user)
{
    uint64_t user_id = (user.type == 1) ? user.id : -1;
    dbi.get_task_id(task_id, user_id);
}

  const f = document.getElementById("chatbox").contentDocument;
  const msg = Buffer(event.data);

  switch (msg[0]) {

  /*
  1. GetTasks for all tasks
  2. GetTaskId for task of certain id with images
  3. GetImageId for just 1 image data
  4. RateIndiv for paired rating. Returns 16 images. Will be 8 different sets.
  5. RatePairs for paired rating. Returns 16 images. Will be 8 different sets.
  6. CreateSequence, creates a new sequence. This also activates a test.
  7. DeleteSequence - deletes a certain sequence
  8. ActivateTest, creates a new test for an already created sequence.
  9. StopTest - stops a certain test
  10. GetUsers -  get data from all users, for admin only
  11. GetUser - get data from a user
  */

    case 10: // GetTasks
      // parse all the tasks
      break;
    case 11: // GetTaskID
      // parse all the images
      break;
    case 12: // RateIndiv
      // rate individual image [group of 8], and get 8 back

      break;
    case 13: // RatePairs
      // rate individual image [group of 16, or 8 pairs]

      break;
    case 14: // CreateSequence
      // Now go to the sequenceID/taskID page
      break;

    case 15: // DeleteSequence
      // say it was successful
      // Go to all tasks
      break;

    case 16: // Activate task
      // say it was successful
      break;

    case 17: // Stop task
      // say it was successful
      break;
    
    case 18: // Get user
      // get your own user data, like the extensions bought + the 
      break;



void parse_input(uint8_t* data)
{
    uint8_t* p = data;

    switch (p) {

    }
}