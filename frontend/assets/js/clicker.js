
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
function rte(url) {
    page = url.split('/').pop()
    //scorerater.style.display='none'
    
    if (page == '') {
        if (loggedIn) {
            gbl.className = 'showRate';
        } else {
            gbl.className = 'showLogin';
        }
    } else if (page == 'tasks') {
        gbl.className = 'showTasks';
        let limit = 0
        let offset = 0
    } else if (page == 'taskID') {
        gbl.className = 'showTaskID';
        let taskID = 1
    } else if (page == 'profile') {
        gbl.className = 'showProfile';
    } else if (page == 'notifications') {
        gbl.className = 'showNotifications';
    } else if (page == 'paired') {
        gbl.className = 'showPaired';
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

var sortDropdownOn = false
var mobilemenuDown = false

function removeDropdowns() {
    if (sortDropdownOn){sortDropdown.classList.remove('show');sortDropdownOn=false;}
    if (auxIconData.prf) {dropp.classList.remove('active');auxIconData.prf=false}
}


let btns = [btnR0,btnR1,btnR2,btnR3,btnR4]

document.onclick = (e) => {
    //alert(e.target)
    //alert(e.target.id)
    var key = e.target.id.slice(-1)

    // link
    if (key == '_') {
        event.preventDefault();
        rte(e.target.href)

        window.history.pushState({},e.target.href,e.target.href)

        removeDropdowns()
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

    //
    else if (key == 'M') {

    }

    // 
    else if (key == 'N') {

    }

    // plus button 
    else if (key == 'R') {
        if (!auxIconData.pls) {
            dropc.classList.add('active')
            auxIconData.pls = true
        } else {
            dropc.classList.remove('active')
            auxIconData.pls = false
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
        if (!sortDropdownOn){sortDropdown.classList.add('show');sortDropdownOn=true;}
        else{sortDropdown.classList.remove('show');sortDropdownOn=false;}
    }

    // dropsort item elements
    else if (key == 'W') {
        if (!sortDropdownOn){sortDropdown.classList.add('show');sortDropdownOn=true;}
        else{sortDropdown.classList.remove('show');sortDropdownOn=false;}
    }

    // square 
    else if (key == 'X') {
        tasks.className = 'squared'
    }
    // rect 
    else if (key == 'Y') {
        tasks.className = 'slideshow'
    }
    // hotdog 
    else if (key == 'Z') {
        tasks.className = 'hlong'
    }

    // remove dropdowns,
    // this is click outside
    else {
        console.log(e)
        removeDropdowns()
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
