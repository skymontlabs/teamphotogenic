
const showClass = [
    'null',
    'showRate',
    'showPaired',
    'showTasks',
    'showTaskID',
    'showImg',
    'showProfile',
    'showLogin',
    'showLogin',
    'showLogin',
    'showLogin',
    'showLogin',
    'showLogin',
    'showLogin',
    'showLogin',
    'showSignup'
]

var PAGES = {
    RATER: 1,
    PAIRED: 2,
    IMAGESETS: 3,
    IMAGESETID: 4,
    IMAGEIDX: 5,
    PROFILE: 6,
    LOGIN: 12,
    SIGNUP: 13
};

const pathnames = {
    '': 1,
    'rate': 1,
    'paired': 2,
    'tasks': 3,
    'taskID': 4,
    'imageID': 5,
    'profile': 6,
    'login': 12,
    'signup': 8
}

const IMAGESET_SORT_FUNCTIONS = ['Date Added','Last Modified','# images']

var DOMSHORTCUTS = {

};

// var CTRLV = {
var CONFIG = {
    // rater
    rScore: null, // score rating
    rTag: 0,   // tag bitfield
    rComment: '', // comment

    // pair
    pairing: [],
    pSel: -1, // picked image

    // imagesets
    iFilter: 7, // filter method
    iSort: 0, // sort method

    // imagesetid
    jId: null, // imageset id
    jImgIdx: null, // image index being selected
    jPairs: [], // how others paired a given image
    jScores: [], // how others scored a given image
    jTags: [], // how others tagged a given image
    jComments: [], // how others commented on a given image

    // premium functions for imagesetid
    // contains all the imageset, to do 2 way comparisons
    xImgIdx: [],

    // login
    lSeed: null,
    wsSpareData: null,


    // uploader
    uTitle: '',
    uAge: 0,
    uGender: 0,
    uDetail: 0,
    uImages: []
};

var CTRLV = {
    iDropdownLUT: {},
    signupStatus: 0
};

// toggle dropdowns and sorts

var SESSION = {
    currentPage: null,
    currentPageStr: null,
    loggedIn: true,
    dropdownOwner: null,
    dropdownOpen: null,
    modalOpen: false,

    nextQueue: [
        [1,20,'img/laurie.jpg'],
        [1,20,'img/lake.jpg'],
        [1,20,'img/square.jpg'],
        [1,20,'img/lake.jpg'],
        [1,20,'img/square.jpg']
    ],
    rateQueue: [],
    prefetchQueue: [],




};


var DATAV = {
    iImagesetList: [
        [1293, ['square.jpg','lake.jpg','square.jpg','lake.jpg','laurie.jpg'], 'joebidengaysex', 13, 1490453218],
        [1932, ['laurie.jpg','square.jpg','square.jpg','laurie.jpg','lake.jpg'], 'joebidengaysex', 13, 1490453218],
        [6969, ['laurie.jpg','square.jpg','laurie.jpg','square.jpg','laurie.jpg'], 'joebidengaysex', 13, 1490453218],
    ],

    iImagesetIDData: [
        [0, 'laurie.jpg', 5.69, 13],
        [1, 'laurie.jpg', 5.69, 13],
        [2, 'laurie.jpg', 5.69, 13],
    ]
};

var BUTTONS = {
    HOME_RATES: [],
    HOME_TAGS: [],
    HOME_PROCEED: null,
};

function clearRater()
{
    CONFIG.rScore = -1;
    CONFIG.rTag = 0;
    CONFIG.rComment = '';
}