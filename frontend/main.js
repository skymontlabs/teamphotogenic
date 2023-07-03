accountLinked.style.display="none";

var page = 1
var cur = editProfilePanel
var loggedin = false

if (page != 0) {
  //dark.style.display="none"
}





editProfileV.onclick = (event)          => {cur.style.display='none';editProfilePanel.style.display='block';cur=editProfilePanel}
securityPrivacyV.onclick = (event)      => {cur.style.display='none';securityPrivacyPanel.style.display='block';cur=securityPrivacyPanel}
addonsV.onclick = (event)               => {cur.style.display='none';addonsPanel.style.display='block';cur=addonsPanel}
redeemV.onclick = (event)               => {cur.style.display='none';redeemPanel.style.display='block';cur=redeemPanel}
displayNotificationsV.onclick = (event) => {cur.style.display='none';displayNotificationsPanel.style.display='block';cur=displayNotificationsPanel}
helpSupportV.onclick = (event)          => {cur.style.display='none';helpSupportPanel.style.display='block';cur=helpSupportPanel}
dark.onclick = (event) => {
    if (loggedin && event.target == dark) {
        dark.style.display='none'
        indvImg.style.display='none'
    }
}

buyCredLi.onclick = (event) => {
    dark.style.display='block'
    dark.style.background='rgba(0,0,0,.6)'
    buyCredData.style.display='flex';
}

signuper.onclick = (event) => {
    const seed = new Uint8Array(16); // get this from the backend, async wait from X
    
    //progress.classList.add('active')
        
    argon2.hash({
      pass: passwordSignup.innerText, salt: seed,
      time: 32, mem: 16384, hashLen: 64,
      type: argon2.ArgonType.Argon2d
    })
    .then(h => {
        // login now
        //sock.send(seedCode->0 + email.length + email)

        dark.classList.add('overlay')
        dark.style.display='none';
        loginer.style.display='none';
        loggedin=true;


        globl.className='showS'
        nV.style.display='block';
    })
    .catch(e => {
        wrongpass.style.display='block'
        console.error('sex')
    })
}


signouter.onclick = (event) => {
    dark.style.display='block';
    loginer.style.display='block';
    loggedin=false;

    //scorerater.style.display='none';
    globl.className=''
    nV.style.display='none';
    prfChx.checked=false

}

activate2f.onclick = (event) => {
    dark.classList.remove('dn')
    panel2f.style.display='block';
}


function fnBrowserDetect(){
  let userAgent = navigator.userAgent;
  let browserName;
  
  if(userAgent.match(/chrome|chromium|crios/i)){
     browserName = "chrome";
   }else if(userAgent.match(/firefox|fxios/i)){
     browserName = "firefox";
     optimum.className=''
   }  else if(userAgent.match(/safari/i)){
     browserName = "safari";
     optimum.className=''
   }else if(userAgent.match(/opr\//i)){
     browserName = "opera";
     optimum.className=''
   } else if(userAgent.match(/edg/i)){
     browserName = "edge";
   }else{
     browserName="No browser detection";
   }
   
   // also track versions
 alert("You are using "+ browserName +" browser");         
}

function routeData () {
    window.history.pushState({},'/avaa',window.location.origin+'/avaa')
}

var scoresImages = []
var scoresCache = []
var tagsCache = []
var commentsCache = []


function scoreRater() {
 // bundle of 32
}

//scoreraterskip
scoreratersubmit.onclick = (event) => {
    inps = document.getElementsByClassName('wrap-togglable')
    console.log(inps)

    for (var i = 0; i < inps.length; ++i) {
        inps[i].children[0].checked=false
    }

    rateEh.checked=false
    rateDe.checked=false
    rateGr.checked=false
    rateSt.checked=false
    rateBr.checked=false

    txa.value=''

/*
    let len = scoresCache.length
    if (len == 32) {
        let ret = ''

        for (let i = 0; i < len; ++i) {
            ret += scoresCache[i];
            ret += tagsCache[i];
            ret += commentsCache[i];
        }


        api_post(, ret)
    }*/
}

function redeem (code) {
    //api('/redeem' + code)
    var item = ''
    redeemMessage.innerText = 'Your code has been successfully redeemed for ' + item
    redeemMessage.innerText = 'Your code is invalid'
}


// image reading


var anchors = document.getElementsByClassName('imgMat');
for(var i = 0; i < anchors.length; i++) {
    var anchor = anchors[i];
    anchor.onclick = function() {
        indvImg.style.display='flex'
        dark.style.display='flex'
    }
}




// setup router

const useHash = true;
const apiUrl = 'https://lucasreta.com/stack-overflow/spa-vanilla-js/api';
const routes = ['section-1', 'section-2'];
const content_box = document.getElementById("content_box");

function get(url) {
    /*alert('Allahu akbar /' + page)*/
    page = url.split('/').pop()
    //scorerater.style.display='none'

    if (page == 'profile') {
        globl.className = "";
        globl.classList.add('showA')


        editProfilePanel.style.display='block'
        editProfileV.children[0].checked=true
    } else if (page == 'securityPrivacy') {
        globl.className = "";
        globl.classList.add('showA')
    } else if (page == 'helpSupport') {
        globl.className = "";
        globl.classList.add('showA')
    } else if (page == 'displayNotifications') {
        globl.className = "";
        globl.classList.add('showA')
        notificationsPanel.style.display='block'
    } else if (page == 'tasks') {
        globl.className = "";
        globl.classList.add('showM')
    } else if (page == 'paired') {
        globl.className = "";
        globl.classList.add('showP')
    } else if (page == '') {
        globl.className = "";
        globl.classList.add('showS')
    } else if (page == 'paired') {
    }
}


const links = document.getElementsByTagName('a');
for(let i = 0; i < links.length; i++) {
  links[i].addEventListener('click', function(event) {
    console.log('lauren')
    event.preventDefault();
    get(links[i].href);

    window.history.pushState({},links[i].href,links[i].href)

    if (prfChx.checked) {
        prfChx.checked=false
    }
  }, false);
}



// clickoutside removal 
//https://stackoverflow.com/questions/152975/how-do-i-detect-a-click-outside-an-element
function onClickOutside() {
  document.addEventListener('click', event => {
    /*alert(event.target)
*/

    console.log(event.target)

    if (!drops.contains(event.target)) {
       //drops.style.display='none'
        //prfChx.checked=true
       //alert('seggs')
    }
  });
};

// Using
onClickOutside();








//window.history.pushState({},'/',window.location.origin+'/')
//window.history.pushState({ data: 'some data' },'Some history entry title', 'main.html');

function create(ratingElem, tagElem, noteElem) {
    //https://measurethat.net/Benchmarks/Show/15720/0/fastest-way-to-list-children-childnodes-vs-children-vs
    rating = ratingElem.get()
    tag = 0
    note = noteElem.innerText

    //for (var i=0;i<;++i){tag|=(tagElem.children[0].checked<<i)}
    let elem = tagElem.firstElementChild;
    do {tag|=(elem.checked<<i)} while (elem = elem.nextElementSibling)

    bytes=[]
}

function get_totp(secret)
{
    secret='GEZDGNBVGY3TQOJQGEZDGNBVGY'
    'otpauth://totp/{name}?secret={secret}&issuer={issuer}'

    S  = 'otpauth://totp/'
    S += name 
    S += '?secret=' 
    S += secret 
    S += '&issuer=' 
    S += issuer 

    for (i = 1000; i > 0; i--) {
      sArr[i] = "String concatenation. ";
    }
    str = sArr.join("");
    var sArr = [];
}







pkey.onclick = (event) => {
  logoDrop.checked=false
  globl.className='showP'
};

rkey.onclick = (event) => {
  logoDrop.checked=false
  globl.className='showS'
};




square.onclick = (event) => {
    myTasks.className='square'
}

rect.onclick = (event) => {
    myTasks.className='rect'
}

hotdog.onclick = (event) => {
    myTasks.className='hotdog'
}

sortMean.onclick = (event) => {sortMethod.innerText='Mean score';sortCheckbox.checked=false}
sortGeo.onclick = (event) => {sortMethod.innerText='Geo Mean score';sortCheckbox.checked=false}
sortHarm.onclick = (event) => {sortMethod.innerText='Harmonic Mean score';sortCheckbox.checked=false}
sortPyth.onclick = (event) => {sortMethod.innerText='Pythago Mean score';sortCheckbox.checked=false}
sortMedian.onclick = (event) => {sortMethod.innerText='Median score';sortCheckbox.checked=false}
sortBayes.onclick = (event) => {sortMethod.innerText='Bayesian Approximation';sortCheckbox.checked=false}
sortQuart.onclick = (event) => {sortMethod.innerText='Lower quartile score';sortCheckbox.checked=false}
sortDate.onclick = (event) => {sortMethod.innerText='Date added';sortCheckbox.checked=false}
sortModi.onclick = (event) => {sortMethod.innerText='Date modified';sortCheckbox.checked=false}



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

function convert2int0(Uint8Arr) {
  var length = Uint8Arr.length;

  let buffer = Buffer.from(Uint8Arr);
  var result = buffer.readUIntBE(0, length);

  return result;
}

function convert2int0(buff) {
  var view = new DataView(buff.buffer, 0);
  view.getUint32(0, true); // true here represents little-endian
}

function parseImageset()
{
//begins with 1 byte # of imagesets listed

/*const uint8 = new Uint8Array([10, 20, 30, 40, 50]);
const array1 = uint8.slice(1, 3);

console.log(array1);
// Expected output: Uint8Array [20, 30]
*/

for (var i = 0; i < 20; ++i) {
  /*[0:8] - photoset ID
  [8:12] - total num images
  [12:16] - total num votes
  [12:16] - total num comments
  [12:16] - score

  [16:24] - imageID 1, HEX 
  [16:24] - url 1, HEX*/
}

}

function parseRate()
{
for (let i = 0; i < 8; ++i) {/*
  // url for image
  [0:8] - imageID
  [8:24] - url*/
}
}

function parsePair()
{
for (let i = 0; i < 8; ++i) {
  // url for image
  /*
  [0:8] - imageID 1
  [8:24] - url 1
  [24:32] - imageID 2
  [32:48] - url 2*/
}
}

function parse()
{
for (let i = 0; i < 8; ++i) {
  // url for image
  /*
  [0:8] - imageID 1
  [8:24] - url 1
  [24:32] - imageID 2
  [32:48] - url 2*/
}
}

function getSeed()
{
let contact = contactInput.innerText
let buff = new ArrayBuffer(3 + contact.length);

buff[0] = 1;
buff[1] = contact.length;
buff[2] = contact[0] == '+';

for (var i = 0; i < contact.length; ++i)
  buff[i + 3] = contact[i]

sk.send(buff,{binary:true});
}

function signup(contact, password, seed)
{
// same as login
let buff = new ArrayBuffer([1 + contact.length + 64]);

argon2.hash({
  pass: password, salt: seed,
  time: 32, mem: 32768, hashLen: 64,
  type: argon2.ArgonType.Argon2d
})
.then(h => {alert(h.hashHex)})
.catch(e => console.error('Signup did not work'))

sk.send(buff,{binary:true});
}

function login(contact, password, seed)
{
let buff = new ArrayBuffer([1 + contact.length + 64]);

argon2.hash({
  pass: password, salt: seed,
  time: 32, mem: 32768, hashLen: 64,
  type: argon2.ArgonType.Argon2d
})
.then(h => {alert(h.hashHex)})
.catch(e => console.error('Login did not work'))

sk.send(buff,{binary:true});
}



      function changePassword(contact, oldPassword, newPassword, oldSeed, newSeed)
      {
        // same as login
        let buff = new ArrayBuffer([1 + contact.length + 64 + 64]);

/*
        argon2.hash({
          pass: password, salt: oldSeed,
          time: 32, mem: 32768, hashLen: 64,
          type: argon2.ArgonType.Argon2d
        })
        .then(h => {buff[1:65] = h.hashHex})
        .catch(e => console.error('Signup did not work'))

        argon2.hash({
          pass: password, salt: newSeed,
          time: 32, mem: 32768, hashLen: 64,
          type: argon2.ArgonType.Argon2d
        })
        .then(h => {buff[1:65] = h.hashHex})
        .catch(e => console.error('Signup did not work'))
*/
        sk.send(buff,{binary:true});
      }


      function submitTOTP(id, input)
      {
        // same as login
        let buff = new ArrayBuffer([8 + 4]);
        sk.send(buff,{binary:true});
      }

      function verifyUser(id)
      {
        let buff = new ArrayBuffer([8]);
        for (var i = 0; i < 8; ++i)
          buff[i] = (id >> 4) & 0xF
        sk.send(id);
      }

      function initTOTP(id, input) {
      }

      function upl()
      {
        let photo = document.getElementById("image-file").files[0];  // file from input
        let req = new XMLHttpRequest();
        let formData = new FormData();

        formData.append("photo", photo);                                
        req.open("POST", '/upload/image');
        req.send(formData);

        data = req.recv()
      }



      imgInp.onchange = evt => {
      console.log(evt)
      console.log(imgInp.files)
      const fi = imgInp.files
      //upImg
      for (let i = 0; i < fi.length; ++i) {
        const div = document.createElement('div')
        const span = document.createElement('span')
        const img = document.createElement('img')
        img.src=URL.createObjectURL(fi[i])
        div.appendChild(img)
        div.appendChild(span)
        upImg.appendChild(div)
        console.log(URL.createObjectURL(fi[i]))
      }

      taskpref.style.display="block"
      imgInp.style.display="none"
      uplList.style.display="none"

      /*
      const [file] = imgInp.files
      console.log(file)
      if (file) {
        blah.src = URL.createObjectURL(file)
      }*/
    }

/*
    upImg.addEventListener('drop', handleDrop, false)

    function handleDrop(e) {
      let dt = e.dataTransfer
      let files = dt.files
      console.log(files)

      //handleFiles(files)
    }
*/
    window.onbeforeunload = function(){
       // Do something
    }

    // OR
    window.addEventListener("beforeunload", function(e){
       // Do something
    }, false);

    document.addEventListener("keydown", (event) => {
      console.log(event)
      if (event.keyCode === 49)
        e0.checked=true
      if (event.keyCode === 50)
        e1.checked=true
      if (event.keyCode === 13) {
        e0.checked=false
        e1.checked=false
      }
    });

    sq = []

    function submit() {
      if (sq.length<20){
        sq.append([rating, e, comments])
      }

      alert('submitted')
    }

/*
(function(fn = function() {
  const page = useHash ?
    window.location.hash.split('#').pop() :
    window.location.href.split('/').pop();
  get(routes.indexOf(page) >= 0 ? page : routes[0]);
}) {
  if (document.readyState != 'loading'){
    fn();
  } else {
    document.addEventListener('DOMContentLoaded', fn);
  }
})();*/