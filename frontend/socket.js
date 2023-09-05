

const sck = new WebSocket("wss://api.teamphotogenic.com/ws", "protocolOne");
sck.binaryType = "arraybuffer";
//sck.onopen = onopen;
//sck.onmessage = onmessage;
sck.onclose = onclose;
sck.onerror = onerror;

seed = null

onbeforeunload = (event) => {console.log('seggs')};


sck.onopen = (event) => {
}

sck.onmessage = (event) => {
  const f = document.getElementById("chatbox").contentDocument;
  const msg = Buffer(event.data);

  switch (msg[0]) {
    case 0: // get seed
      seed = ArrayBuffer(msg, 1, 20)
      break;
    case 1: // login
      msg = data

      localStorage.setItem("token", ArrayBuffer(msg, 1));
      break;
    case 2: // signup
      "Username exists"

      "Check code"
      break;
    case 3: // submit totp 
      let password = ArrayBuffer(msg, 1)

      // goes to login

      break;
    case 4: // init change password
      // get old seed and new seed
      let oldSeed = ArrayBuffer(msg, 1)
      let newSeed = ArrayBuffer(msg, 1)

      changePassword(contact, oldPassword, newPassword, oldSeed, newSeed)
      break;
    case 5: // change password
      "Password changed"
      break;
    case 6: // verify acct
      msg = data

      localStorage.setItem("token", ArrayBuffer(msg, 1));
      break;
    case 7: // init totp 
      "";
      break;
    case 8: // add totp
      "";
      break;
    case 9: // remove totp
      "TOTP Removed"
      break;

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
  }
};