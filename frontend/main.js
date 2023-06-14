function routeData () {
    window.history.pushState({},'/avaa',window.location.origin+'/avaa')
}

var cur = editProfilePanel
var loggedin = false

editProfileV.onclick = (event)          => {cur.style.display='none';editProfilePanel.style.display='block';cur=editProfilePanel}
securityPrivacyV.onclick = (event)      => {cur.style.display='none';securityPrivacyPanel.style.display='block';cur=securityPrivacyPanel}
addonsV.onclick = (event)               => {cur.style.display='none';addonsPanel.style.display='block';cur=addonsPanel}
redeemV.onclick = (event)               => {cur.style.display='none';redeemPanel.style.display='block';cur=redeemPanel}
displayNotificationsV.onclick = (event) => {cur.style.display='none';displayNotificationsPanel.style.display='block';cur=displayNotificationsPanel}
helpSupportV.onclick = (event)          => {cur.style.display='none';helpSupportPanel.style.display='block';cur=helpSupportPanel}
dark.onclick = (event) => {
    if (loggedin && event.target == dark) {
        //alert('del')
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
    dark.classList.add('overlay')
    dark.style.display='none';
    loginer.style.display='none';
    loggedin=true;

    //scorerater.style.display='block';
    globl.className='showS'
    nV.style.display='block';

    //emailSignup.innerText

    //sock.send(seedCode->0 + email.length + email)


    // WAIT


    const seed = new Uint8Array(16); // get this from the backend, async wait from X
    argon2.hash({
      pass: passwordSignup.innerText, salt: seed,
      time: 24, mem: 16384, hashLen: 64,
      type: argon2.ArgonType.Argon2d
    })
    .then(h => {alert(h.hashHex)})
    .catch(e => console.error('sex'))
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