
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
            gbl.className = 'showRate';
        } else {
            gbl.className = 'showLogin';
        }
    } else if (pg==='tasks') {
        console.log('tasks yee')
        gbl.className = 'showTasks';
        let limit = 0
        let offset = 0

        for (let i = 0; i < 10; ++i) {
            taskData()
        }
    } else if (pg==='taskID') {
        gbl.className = 'showTaskID';
        let taskID = 1

        for (let i = 0; i < 10; ++i) {
            imageIndiv()
        }
    } else if (pg==='imageID') {
        gbl.className = 'showTasks showImg';
        let taskID = 1

        for (let i = 0; i < 10; ++i) {
            imageIndiv()
        }
    } else if (pg==='settingsz') {
        gbl.className = 'showTaskID';
        let taskID = 1
    } else if (pg==='login') {
        gbl.className = 'showLogin';
    } else if (pg==='signup') {
        gbl.className = 'showSignup';
    } else if (pg==='statistics') {
        gbl.className = 'showTaskID';
        let taskID = 1
    } else if (pg==='profile') {
        if (hh==='') {gbl.className = 'showProfile';}
        else if (hh==='settings') {gbl.className = 'showProfile';}
        else if (hh==='premium') {gbl.className = 'showProfile';}
        else if (hh==='password') {gbl.className = 'showProfile';}
        else if (hh==='notif') {gbl.className = 'showProfile';}
        else if (hh==='help') {gbl.className = 'showProfile';}
        else {alert('phucc')}
    } else if (pg==='notifications') {
        gbl.className = 'showNotifications';
    } else if (pg==='paired') {
        gbl.className = 'showPaired';
    } else {
        alert('phucc')
    }
}


rte(window.location.pathname)

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
/*

let auxIconData = {
    que: false,
    nof: false,
    prf: false,
    pls: false
};
*/

var questionDropdownOn = false
var notificDropdownOn = false
var profileDropdownOn = false
var plusDropdownOn = false

function removeDropdowns(idxv) {
    if (sortDropdownOn){sortDropdown.classList.remove('show');sortDropdownOn=false;return idxv==0}
    if (auxIconData.prf) {dropp.classList.remove('active');auxIconData.prf=false;return idxv==1}
    if (dotOptions) {bblDropdown.classList.remove('show');dotOptions=false;return idxv==2}
    if (notificDropdownOn) {dropn.classList.remove('active');notificDropdownOn=false;return idxv==3}
    if (questionDropdownOn) {dropi.classList.remove('active');questionDropdownOn=false;return idxv==4}
    if (plusDropdownOn) {dropc.classList.remove('active');plusDropdownOn=false;return idxv==5}
    if (filtDropdownOn){filtDropdown.classList.remove('show');filtDropdownOn=false;return idxv==6}
    return false
}

let btns = [btnR0,btnR1,btnR2,btnR3,btnR4]
let activeImageSort = daq

document.onclick = (e) => {
    var key = e.target.id.slice(-1)

    // link
    if (key == '_') {
        event.preventDefault();
        rte(e.target.href)
        window.history.pushState({},e.target.href,e.target.href)
        removeDropdowns(-1)
    }

    // rating 
    else if (key >= '0' && key <= '4') {
        if (ratingData.rating != -1) {
            btns[ratingData.rating].classList.remove('active')
        }

        console.log(key - '0')
        btns[key - '0'].classList.add('active')
        ratingData.rating = key - '0'
        rateData.classList.add('tagsLevel')
    }
    
    // tag 
    else if ((key >= '5' && key <= '9') || (key >= 'A' && key <= 'F')) {
        //alert('tagged', e.target)
        e.target.classList.add('active')
    }

    // DARK 
    else if (key == 'k') {
        alert('dark')
        gbl.className = 'showTasks'
        rte('/taskID')
        window.history.pushState({},'/taskID','/taskID')

    }


    // skip 
    else if (key == 'G') {

    }

    // report
    else if (key == 'H') {

    }

    // submit 
    else if (key == 'I') {

    }

    // image indivual toggle
    else if (key == 'J') {

    }

    // image slideshow toggle
    else if (key == 'K') {

    }

    //  hamburger
    else if (key == 'L') {
        if (!mobilemenuDown){nv.className='active';mobilemenuDown=true;}
        else{nv.className='a';mobilemenuDown=false;}
    }

    // edit test
    else if (key == 'M') {
        // 
    }

    // delete test
    else if (key == 'N') {

    }

    // AVERAGE SCORE button 
    else if (key == 'O') {

    }

    // MEDIAN SCORE button 
    else if (key == 'P') {

    }

    // LOWER QUARTILE button 
    else if (key == 'Q') {
        // this is always remove, most important is to change
        sortDropdown.classList.remove('show');
        sortDropdownOn=false;

        console.log(e.target)

    }

    // plus button 
    else if (key == 'R') {
        if (!plusDropdownOn) {
            dropc.classList.add('active')
            plusDropdownOn = true
        } else {
            dropc.classList.remove('active')
            plusDropdownOn = false
        }
    }

    // documentation button 
    else if (key == 'S') {

    }

    // dropdown, notifications
    else if (key == 'T') {
        if (!auxIconData.nof) {
            dropp.classList.remove('active')
            auxIconData.prf = false

            dropn.classList.add('active')
            auxIconData.nof = true
        } else {
            dropn.classList.remove('active')
            auxIconData.nof = false
        }
    }

    // dropdown, profile
    else if (key == 'U') {

        //if (!removeDropdowns(1)) {}
        if (!auxIconData.prf) {
            dropn.classList.remove('active')
            auxIconData.nof = false

            dropp.classList.add('active')
            auxIconData.prf = true
        } else {
            dropp.classList.remove('active')
            auxIconData.prf = false
        }
    }

    // dropsort item title
    else if (key == 'V') {
        if (!removeDropdowns(0)) {
            if (!sortDropdownOn){sortDropdown.classList.add('show');sortDropdownOn=true;}
            else{sortDropdown.classList.remove('show');sortDropdownOn=false;}
        }
    }

    // dropsort filter elements
    else if (key == 'W') {
        if (!removeDropdowns(6)) {
            if (!filtDropdownOn){filtDropdown.classList.add('show');filtDropdownOn=true;}
            else{filtDropdown.classList.remove('show');filtDropdownOn=false;}
        }
    }

    // dot options 
    else if (key == 'X') {
        if (!removeDropdowns(2)) {
            if (!dotOptions){bblDropdown.classList.add('show');dotOptions=true;}
            else{bblDropdown.classList.remove('show');dotOptions=false;}
        }
    }

    // resume test 
    else if (key == 'Y') {
    }

    // pause test 
    else if (key == 'Z') {
        tasks.className = 'hlong'
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
