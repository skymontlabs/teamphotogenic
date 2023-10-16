
// dropdown for aux icons in nav
let auxIconData = {
    que: false,
    nof: false,
    prf: false,
    pls: false
};

// hamburger for main menu in nav
function s() {

}
var loggedIn = true
let W=window

window.onhashchange = function() {
 //blah blah blah
    alert('hashchange')
}

window.onpopstate = function(event) {
    alert('back or forward triggered')
    rte(event.target.location.pathname)
}

function rte(url) {
    let pg = url.split('/').pop()
    let hh = window.location.hash

    if (pg==='') {
        if (loggedIn) {
            Ga.className = 'showRate';
        } else {
            Ga.className = 'showLogin';
        }
    } else if (pg==='tasks') {
        console.log('tasks yee')
        Ga.className = 'showTasks';
        let limit = 0
        let offset = 0

        for (let i = 0; i < 1; ++i) {
            taskData()
        }
    } else if (pg==='taskID') {
        Ga.className = 'showTaskID';
        let taskID = 1

        for (let i = 0; i < 1; ++i) {
            imageIndiv()
        }
    } else if (pg==='imageID') {
        Ga.className = 'showTasks showImg';
        let taskID = 1

        for (let i = 0; i < 1; ++i) {
            imageIndiv()
        }
    } else if (pg==='profile') {
        Ga.className = 'showProfile edit';
    } else if (pg==='security') {
        Ga.className = 'showProfile sec';
    } else if (pg==='alerts') {
        Ga.className = 'showProfile alr';
    } else if (pg==='billing') {
        Ga.className = 'showProfile bil';
    } else if (pg==='help') {
        Ga.className = 'showProfile hlp';
    } else if (pg==='login') {
        Ga.className = 'showLogin';
    } else if (pg==='signup') {
        Ga.className = 'showSignup';
    } else if (pg==='statistics') {
        Ga.className = 'showTaskID';
        let taskID = 1
    } else if (pg==='notifications') {
        Ga.className = 'showNotifications';
    } else if (pg==='paired') {
        Ga.className = 'showPaired';
    } else if (pg==='premium') {
        Ga.className = 'showPremium';
    } else {
        alert('phucc')
    }

    //window.history.pushState({},e.target.href,e.target.href)
}


rte(window.location.pathname)
window.history.pushState({},window.location.pathname,window.location.pathname)

function updateHistory(curr) {
    window.location.lasthash.push(window.location.hash);
    window.location.hash = curr;
}

function goBack() {
    window.location.hash = window.location.lasthash[window.location.lasthash.length-1];
    window.location.lasthash.pop();
}

var dotOptions = false
var sortDropdownOn = false
var filtDropdownOn = false
var mobilemenuDown = false

var questionDropdownOn = false
var notificDropdownOn = false
var profileDropdownOn = false
var plusDropdownOn = false



var OPN = -1 // this represents the id that is opened
var FIL = -1 // controls if filter is open

/*
  <ul id="zDropdown" class="dropsort">
    <li id="Sd0" class="noselect active">Delete test</li>
    <li id="Sd1" class="noselect active">Pause test</li>
    <li id="Sd2" class="noselect active">Restart test</li>
    <li id="Sd3" class="noselect active"> test</li>
  </ul>
*/


function removeDropdowns(idxv) {
    if (OPN==-1) {return true}

    switch (OPN) {
        case 1: // mobile hamburger menu for nav
            // previously was 'A'
            Na.className=''
        case 2: // logo dropdown
            // previously had 'A'
            Da.className='dropdown BlA'
        case 3: // nav notification dropdown
            // previously had 'A'
            dea.className='dropdown'
            break
        case 4: // profile dropdown
            // previously had 'A'
            dfa.className='dropdown'
            break
        case 5: // rate more dropdown (reports, etc)
            // previously had 'A'
            rMor.className='dropsort'
            break
        case 6: // dots for edit/delete task in /taskID
            // previously had 'A'
            Da.className='dropdown BlA'
            break
        case 7: // dots for edit/delete task in grid /tasks
            // previously had 'A'
            Da.className='dropdown BlA'
            break
        case 8: // sort dropdown for /tasks
            sortDropdown.className='dropsort'
            break
        case 9: // filter dropdown for /tasks
            Da.className='dropdown BlA'
            break
        case 10: // date dropdown in /profile
            DAT.className='dropdown BlA'
            break
        case 11: // language dropdown in /profile
            LNG.className='dropdown BlA'
            break
        case 100: // new test upload modal
            // previously was 'U'
            ZZ.className='A'
            break
        default:
            break
    }

    let ov = OPN
    OPN=-1
    return (idxv!==ov)
}


let cRate=-1
let cTg=0
let cLanguage=-1
let cStatus=0
let cSortVal=0

document.onclick = (e) => {
    let tG=e.target
    let H=e.target.id
    let key=H.slice(-1)
    console.log(H)

    // link
    if (key === '_') {
        event.preventDefault();
        rte(e.target.href)
        window.history.pushState({},e.target.href,e.target.href)
        removeDropdowns(-1)
    }

////// navigation #Na
    if (tG === Bc) {
        if (removeDropdowns(1)) {Na.className='A';OPN=1}
    }

    else if (Lb.contains(tG)) {
        if (removeDropdowns(2)) {Da.className='dropdown BlA A';OPN=2}
    }


    else if (tG===Je||tG===Ke||tG===Le) {
        if (removeDropdowns(3)) {dea.className='dropdown BlA A';OPN=3}
    }


    else if (tG===Jf||tG===Kf||tG===Lf) {
        if (removeDropdowns(4)) {dfa.className='dropdown BlA A';OPN=4}
    }

    // new test upload modal
    else if (tG===Pd) {
        alert('seg')
        if (removeDropdowns(100)) {Ga.className='showUpl';OPN=100}
    }


////// / page (rater)

    // rating 
    else if (Ca.contains(tG) && tG !== Ca) {
        let aidx=key - '0'
        if (cRate!==-1){Ca.children[cRate].className='btn BR';}
        Ca.children[aidx].className='btn BR A';
        cRate = aidx
    }

    // tag 
    else if (Ua.contains(tG) && tG !== Ua) {
        let aidx=key.charCodeAt(0) - 97
        //console.log(aidx)
        if (cTg&(1<<aidx)){Ua.children[aidx].className='BZ';cTg ^= (1<<aidx);}
        else{Ua.children[aidx].className='BZ A';cTg |= (1<<aidx);}
    }
    
    // dropdown
    else if (Dmo.contains(tG)) {
        console.log('69420')
        if (removeDropdowns(5)) {rMor.className='dropsort A';OPN=5}
    }

    // report
    else if (Rpt.contains(tG)) {
        console.log('report')
    }

    // skip
    else if (Sk.contains(tG)) {
        console.log('skip')
    }

    // submit
    else if (Sm.contains(tG)) {
        console.log('submit')
    }

////// /paired page
    else if (IWa.contains(tG)) {
        console.log('pic a')
    }

    else if (IWb.contains(tG)) {
        console.log('pic b')
    }

////// /tasks page

    // sort method in tests 
    else if (tG === sortMethodV) {
        if (removeDropdowns(8)) {sortDropdown.className='dropsort show active A';OPN=8}
    }


    // view all regardless of task status
    else if (tflta.contains(tG) && tG !== tflta) { //a === vAll
        let aidx=key - '0'
        // make sure this is not 0 samples!
        if (cStatus!==aidx) {
            tflta.children[cStatus].className='btn'
            tflta.children[aidx].className='btn A'
            cStatus=aidx

            // refresh page
        }
    }

    else if (sortDropdown.contains(tG) && tG !== sortDropdown) {
        let aidx=key - '0'

        sortMethodV.innerText = sortDropdown.children[aidx].innerText
        
        console.log('seg')
    }

/*
    // view tasks of current run status
    else if (tG === vRun) {
    }

    // view tasks of paused status
    else if (tG === vPau) {
    }

    // view tasks of finished status
    else if (tG === vFin) {
    }
*/

////// DARK 
    else if (tG == ZZ) {
        alert('dark')
        Ga.className = 'showTasks'
        rte('/taskID')
        window.history.pushState({},'/taskID','/taskID')
    }

////// /profile page

    // email
    else if (EiEml.contains(tG)) {
        console.log('same procedure as /rater tag')
    }

    // phone country code

    // phone edit
    else if (EiEml.contains(tG)) {
        console.log('same procedure as /rater tag')
    }

    // gender
    else if (pGda.contains(tG)) {
        console.log('same procedure as /rater tag')
    }

    // activity
    else if (pHbt.contains(tG)) {
        console.log('same procedure as /rater tag')
    }

    // dropdown for language
    else if (lndr.contains(tG)) {
        if (removeDropdowns(11)) {LNG.className='dropsort A';OPN=11}
    }

    // picked a language
    else if (LNG.contains(tG)) {
        console.log('picked language, same procedure as /rater tag, now remove dropdown and change language')
    }



    // image indivual toggle
    // image slideshow toggle
    // edit test
    // delete test
    // AVERAGE SCORE button 

    // MEDIAN SCORE button 

    // LOWER QUARTILE button 

    //  hamburger
    else if (key == 'c') {
    }

    // plus button 
    else if (key == 'd') {
    }

    // notifications button 
    else if (key == 'e') {
    }

    // notifications button 
    else if (key == 'f') {
    }

    // dropdown, profile
    else if (key == 'f') {

    }

    // dropdown, profile
    else if (key == 'g') {

    }

    // dropsort item title
    else if (key == 'V') {
    }

    // dropsort filter elements
    else if (key == 'W') {
    }

    // dot options 
    else if (key == 'X') {
    }

    // resume test 
    else if (key == 'Y') {
    }

    // pause test 
    else if (key == 'ZZZ') {
    }

    // logo dropdown
    else if (key == 'b') {
    }

    //  

    // sign up
    else if (key == 'q') {
        rte('/')
        window.history.pushState({},'/','/')
    }

    // sign out
    else if (key == 'r') {
        console.log('seggs')
        rte('/login')
        window.history.pushState({},'/login','/login')
    }

    // status filter dropdown
    else if (key == 'y') {
        console.log('seg')
        stusDrop.classList.toggle('show')
    }

    // remove dropdowns,
    // this is click outside
    else {
        console.log('remove dropdown')

        removeDropdowns(-1)
    }
    
    // report
    // skip
    // submit
    
    // check if any dropdowns are open

};


// toggle rating
let ratingData = {
    rating: -1,
    tags: -1,
    note: ''
};



/*
for (var i = 0; i < 13; i++) {
    console.log(optTag.children[i])

}*/


// toggle dropdown for sort by in tasks

// toggle structure of indiv task in tasks

// click outside for
// - sortMethod
// - dropdowns for aux icons
var specifiedElement = document.getElementById('a');

/*
document.addEventListener('click', function(event) {
  var isClickInside = specifiedElement.contains(event.target);
  if (isClickInside) {
    alert('You clicked inside A')
  } else {
    alert('You clicked outside A')
  }
});
*/

















// oninputchange


/*

function controlFromInput(fromSlider, fromInput, toInput, controlSlider) {
    const [from, to] = getParsed(fromInput, toInput);
    fillSlider(fromInput, toInput, '#C6C6C6', '#25daa5', controlSlider);
    if (from > to) {
        fromSlider.value = to;
        fromInput.value = to;
    } else {
        fromSlider.value = from;
    }
}
    
function controlToInput(toSlider, fromInput, toInput, controlSlider) {
    const [from, to] = getParsed(fromInput, toInput);
    fillSlider(fromInput, toInput, '#C6C6C6', '#25daa5', controlSlider);
    setToggleAccessible(toInput);
    if (from <= to) {
        toSlider.value = to;
        toInput.value = to;
    } else {
        toInput.value = from;
    }
}

function controlFromSlider(fromSlider, toSlider, fromInput) {
  const [from, to] = getParsed(fromSlider, toSlider);
  fillSlider(fromSlider, toSlider, '#C6C6C6', '#25daa5', toSlider);
  if (from > to) {
    fromSlider.value = to;
    fromInput.value = to;
  } else {
    fromInput.value = from;
  }
}

function controlToSlider(fromSlider, toSlider, toInput) {
  const [from, to] = getParsed(fromSlider, toSlider);
  fillSlider(fromSlider, toSlider, '#C6C6C6', '#25daa5', toSlider);
  setToggleAccessible(toSlider);
  if (from <= to) {
    toSlider.value = to;
    toInput.value = to;
  } else {
    toInput.value = from;
    toSlider.value = from;
  }
}

function getParsed(currentFrom, currentTo) {
  const from = parseInt(currentFrom.value, 10);
  const to = parseInt(currentTo.value, 10);
  return [from, to];
}

function fillSlider(from, to, sliderColor, rangeColor, controlSlider) {
    const rangeDistance = to.max-to.min;
    const fromPosition = from.value - to.min;
    const toPosition = to.value - to.min;
    controlSlider.style.background = `linear-gradient(
      to right,
      ${sliderColor} 0%,
      ${sliderColor} ${((fromPosition)/(rangeDistance)*100)+5}%,
      ${rangeColor} ${(((fromPosition)/(rangeDistance))*100)+5}%,
      ${rangeColor} ${((toPosition)/(rangeDistance)*100)-2}%, 
      ${sliderColor} ${((toPosition)/(rangeDistance)*100)-2}%, 
      ${sliderColor} 100%)`;
}

function setToggleAccessible(currentTarget) {
  const toSlider = document.querySelector('#toSlider');
  if (Number(currentTarget.value) <= 0 ) {
    toSlider.style.zIndex = 2;
  } else {
    toSlider.style.zIndex = 0;
  }
}

const fromSlider = document.querySelector('#fromSlider');
const toSlider = document.querySelector('#toSlider');
const fromInput = document.querySelector('#fromInput');
const toInput = document.querySelector('#toInput');
fillSlider(fromSlider, toSlider, '#C6C6C6', '#25daa5', toSlider);
setToggleAccessible(toSlider);

fromSlider.oninput = () => controlFromSlider(fromSlider, toSlider, fromInput);
toSlider.oninput = () => controlToSlider(fromSlider, toSlider, toInput);
fromInput.oninput = () => controlFromInput(fromSlider, fromInput, toInput, toSlider);
toInput.oninput = () => controlToInput(toSlider, fromInput, toInput, toSlider);


*/