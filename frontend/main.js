

//
// DROPDOWNS BEGIN
//
var ziv=0,znv=0,zpv=0;
//infTog.onclick = (event) => {console.log('sex');if(ziv==0){dropi.style.display='block';ziv=1}else{dropi.style.display='none';ziv=0}dropn.style.display='none';dropp.style.display='none';znv=0;zpv=0;}
//notTog.onclick = (event) => {if(znv==0){dropn.style.display='block';znv=1}else{dropn.style.display='none';znv=0}dropi.style.display='none';dropp.style.display='none';ziv=0;zpv=0}
//prfTog.onclick = (event) => {if(zpv==0){dropp.style.display='block';zpv=1}else{dropp.style.display='none';zpv=0}dropi.style.display='none';dropn.style.display='none';ziv=0;znv=0}
//
// DROPDOWNS END
//


accountLinked.style.display="none";

var initPage = 1
var cur = editProfilePanel
var loggedin = false

//const pageVal = localStorage.getItem("pageVal");


if (!loggedin) {
  // login now through socket

  dark.classList.add('overlay')
  dark.style.display='none';
  loginer.style.display='none';
  loggedin=true;
  globl.className='showS'
  nv.style.display='block';
} else {
  dark.style.display='flex'
}




dark.onclick = (event) => {
  if (loggedin && event.target == dark) {
    dark.style.display='none'
    indvImg.style.display='none'
    buyCredData.style.display='none';
    uploader.style.display='none';
  }
}

buyCredLi.onclick = (event) => {
  dark.style.display='block'
  dark.style.background='rgba(0,0,0,.6)'
  buyCredData.style.display='flex';
}

newPost.onclick = (event) => {
  dark.style.display='block'
  dark.style.background='rgba(0,0,0,.6)'
  uploader.style.display='block';
}

signuper.onclick = (event) => {
  const seed = new Uint8Array(16); // get this from the backend, async wait from X
  
  argon2.hash({
    pass: passwordSignup.innerText, salt: seed,
    time: 32, mem: 16384, hashLen: 64,
    type: argon2.ArgonType.Argon2d
  })
  .then(h => {
    //sock.send(seedCode->0 + email.length + email)

    dark.classList.add('overlay')
    dark.style.display='none'
    loginer.style.display='none'
    loggedin=true

    globl.className='showS'
    nV.style.display='block'
  })
  .catch(e => {
    wrongpass.style.display='block'
    console.error('incorrect')
  })
}

signouter.onclick = (event) => {
    dark.style.display='block';
    dark.className='';
    loginer.style.display='block';
    loggedin=false;

    globl.className=''
    nV.style.display='none';
    prfTog.checked=false
}

activate2f.onclick = (event) => {
    dark.classList.remove('dn')
    panel2f.style.display='block';
}


function fnBrowserDetect(){
  let userAgent = navigator.userAgent;
  let browserName;
  
  if (userAgent.match(/chrome|chromium|crios/i)){
    browserName = "chrome";
  } else if(userAgent.match(/firefox|fxios/i)){
    browserName = "firefox";
    optimum.className=''
  } else if(userAgent.match(/safari/i)){
    browserName = "safari";
    optimum.className=''
  } else if(userAgent.match(/opr\//i)){
    browserName = "opera";
    optimum.className=''
  } else if(userAgent.match(/edg/i)){
    browserName = "edge";
  } else{
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
}

function save() {
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

square.onclick = (event) => {tasks.className='square';filterTagsWrapper.style.display='none'}
rect.onclick = (event) => {tasks.className='rect';filterTagsWrapper.style.display='none'}
hotdog.onclick = (event) => {tasks.className='hotdog';filterTagsWrapper.style.display='none'}
/*
imgbulk.onclick = (event) => {tasks.className='imgbulk';filterTagsWrapper.style.display='flex'}*/

sortMean.onclick = (event) => {sortMethod.innerText='Mean score';sortCheckbox.checked=false}
sortGeo.onclick = (event) => {sortMethod.innerText='Geo Mean score';sortCheckbox.checked=false}
sortHarm.onclick = (event) => {sortMethod.innerText='Harmonic Mean score';sortCheckbox.checked=false}
sortPyth.onclick = (event) => {sortMethod.innerText='Pythago Mean score';sortCheckbox.checked=false}
sortMedian.onclick = (event) => {sortMethod.innerText='Median score';sortCheckbox.checked=false}
sortBayes.onclick = (event) => {sortMethod.innerText='Bayesian Approximation';sortCheckbox.checked=false}
sortQuart.onclick = (event) => {sortMethod.innerText='Lower quartile score';sortCheckbox.checked=false}
sortDate.onclick = (event) => {sortMethod.innerText='Date added';sortCheckbox.checked=false}
sortModi.onclick = (event) => {sortMethod.innerText='Date modified';sortCheckbox.checked=false}



function convert2int0(Uint8Arr) {
  var length = Uint8Arr.length
  let buffer = Buffer.from(Uint8Arr)
  var result = buffer.readUIntBE(0, length)

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
  if (paired) {
    //put rest in here
  }
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