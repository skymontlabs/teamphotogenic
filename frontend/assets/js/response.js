// Function to read a 
function readInt48LE(bytes, offset) {
    return (bytes[offset] | (bytes[offset + 1] << 8) | (bytes[offset + 2] << 16) | (bytes[offset + 3] << 24) | (bytes[offset + 4] << 32) | (bytes[offset + 5] << 40)) >>> 0;
}

// Function to read a 32-bit integer from a byte offset, assuming little-endian
function readInt32LE(bytes, offset) {
    return (bytes[offset] | (bytes[offset + 1] << 8) | (bytes[offset + 2] << 16) | (bytes[offset + 3] << 24)) >>> 0;
}

// Function to read a 16-bit integer from a byte offset, assuming little-endian
function readInt16LE(bytes, offset) {
    return bytes[offset] | (bytes[offset + 1] << 8);
}

function generateImagesetIDCard()
{
    //taskData does this already
}

function generateImageIDCard()
{
    // 
}

function gotoHome()
{
    SESSION.currentPage = PAGES.RATER
    SESSION.currentPageStr = '/'
    SESSION.loggedIn = true

    rte('/')
    window.history.pushState({},'/','/')
}

function clearConfig()
{

}

function readNotification()
{
    //1 = finished imageset
    //2 = stopped imageset due to lack of credits
    //3 = finished image within imageset (usually optional)
    let nf = []

    switch (byte) {
    case 1:
        nf.push()
        break;
    case 2:
        nf.push()
        break;
    case 3:
        nf.push()
        break;
    }
}

function readImageIdx()
{
    let imgIdx     = bytes[0]; // image idx
    let ratingsCt  = readInt32LE(bytes, 1); // ratings ct
    let commentCt  = readInt32LE(bytes, 5); // comments ct
    let pairs      = []
    let ratings    = []
    let scores     = []
    let ratings    = []
    let jTags      = []
    let comments   = []

    // read tags
    for (let i = 0; i < CONSTANTS.TAGCT; ++i) {
        tags.push(readInt32LE(bytes, i * 4 + 9))
    }
    
    // read ratings
    for (let i = 0; i < ratingsCt; ++i) {
        ratings.push(readInt32LE(bytes, i * 4 + 9 + (4 * CONSTANTS.TAGCT)))
    }

    // read comments
    let offsetBytes = 
    for (let i = 0; i < commentCt; ++i) {
        let com = readComment(bytes, offsetBytes)
        offsetBytes = com.offset

        comment.push(com)
    }
}

// START CPP

function readImageIdxCPP() // serialize()
{
    WRITE8(idx)
    WRITE32(ratingsCt)
    WRITE32(commentCt)

    // read tags
    for (int i = 0; i < TAG_CT; ++i) {
        WRITE32(tag_histogram[i])
    }
    
    // read ratings
    vector<string_view> comments;
    for (let i = 0; i < ratings_ct; ++i) {
        WRITE32(ratings[i].score)
        if (ratings[i].comment) comments.push_back(ratings[i]);
    }

    // read comments
    for (let i = 0; i < comment_ct; ++i) {
        WRITESTR(p, comments[i].data(), comments[i].size())
    }

    return p - begin;
}


function readImageIdxPreviewCPP() // when you are on /imageset/:id and need a list of all the images
{
    WRITE8(idx)
    WRITE32(ratingsCt)
    WRITE32(commentCt)

    // read tags
    for (int i = 0; i < TAG_CT; ++i) {
        WRITE32(tag_histogram[i])
    }
    
    // read ratings
    vector<string_view> comments;
    for (let i = 0; i < ratings_ct; ++i) {
        WRITE32(ratings[i].score)
        if (ratings[i].comment) comments.push_back(ratings[i]);
    }

    return p - begin;
}


function readImageIdxDetailedCPP() // serialize()
{
    // each individual rating....
}

function findRatingsCPP()
{
    auto breakpoint = (priority_size * 3);
    auto maxpoint = (breakpoint + standard_size);
    auto rd = random(maxpoint);
    image* img;

    WRITE32(p, type=GET_RATINGS)
    WRITE32(p, length=63)

    for (int i = 0; i < 8; ++i) {
        loop_queue* lq = (rd < breakpoint) ? fast_queue : slow_queue;
        img = lq.get_top().imgs_queue.get_top();

        WRITE48(p, images[i].imageset_id)
        WRITE8(p, img.image_idx)
    }
}

function findPairingsCPP()
{
    // do the same as ratings except change a few factors.
    // 
    auto breakpoint = (priority_size * 3);
    auto maxpoint = (breakpoint + standard_size);
    auto rd = random(maxpoint);
    image* img;

    WRITE32(p, type=GET_RATINGS)
    WRITE32(p, length=64)

    for (int i = 0; i < 8; ++i) {
        loop_queue* lq = (rd < breakpoint) ? fast_queue : slow_queue;
        img0 = lq.get_top().imgs_queue.get_top();
        img1 = lq.get_top().imgs_queue.get_top();

        WRITE48(p, images[i].imageset_id)
        WRITE8(p, images[i].image_idx)
        WRITE8(p, images[i].image_idx)
    }
}

function readImagesetsCPP() // serialize()
{
    WRITE48(imagesetCt)

    for (int i = 0; i < imagesetCt; ++i) {
        auto id = user.imageset_idxs[i];
        auto ims = imagesets[id];

        WRITE48(p, imageset_id)
        WRITE48(p, ims.timestamp)
        WRITE48(p, ims.comment_ct)
        WRITE8(p, ims.imgCt)
        WRITE8(p, ims.imgIdx0)
        WRITE8(p, ims.imgIdx1)
        WRITE8(p, ims.imgIdx2)
        WRITE8(p, ims.imgIdx3)
    }
}

function readImagesetsPreloaderCPP() // serialize()
{
    WRITE48(imagesetCt)

    for (int i = 0; i < imagesetCt; ++i) {
        auto id = user.imageset_idxs[i];
        auto ims = imagesets[id];

        WRITE48(p, ims.imageset_id)
        WRITESTR(p, ims.title)
        WRITE48(p, ims.timestamp)
        WRITE32(p, ims.comment_ct)
        WRITE16(p, ims.img_ct)
        WRITE8(p, ims.contiguous)

        for (int j = 0; j < imgCt; ++i)
        {
            // image idx is optional 
            auto img = ims.images[j];
            if (!ims.contiguous) {
                WRITE16(p, img.idx)
            }
            WRITE48(p, img.comments_ct)
            WRITE32(p, img.rating_ct)
            WRITE16(p, img.rating_avg)
            WRITE16(p, img.rating_lowest_img)
            WRITE16(p, img.rating_highest_img)
        }
    }
}

function readImagesetsCPP()
{
    if (usr.num_imsets > 3) {
        readImagesetsCPP()
    } else if (usr.has_currently_running) {
        // only do current ones
        readImagesetsPreloaderCPP()
    } else {
        // if there is not a current one.
        readImagesetsPreloaderCPP()
    }
}

function readImagesetIDCPP() // serialize()
{
    // get an imageset and all its images
    WRITE48(imageCt)
    WRITE48(imagesetID)
    WRITESTR(imagesetTitle)

    for (let i = 0; i < imageCt; ++i) {
        WRITE16(p, id) // image idx [8]
        WRITE48(p, comments_ct) // comments [12]

        WRITE32(p, rating_ct)
        WRITE16(p, rating_avg)
        WRITE16(p, rating_lowest_img)
        WRITE16(p, rating_highest_img)
    }
}


// END CPP
async function convertBlobToUint8Array(blob) {
  try {
    // Read the blob as an ArrayBuffer
    const arrayBuffer = await blob.arrayBuffer();
    // Create a Uint8Array view on the ArrayBuffer
    const uint8Array = new Uint8Array(arrayBuffer);
    return uint8Array;
  } catch (error) {
    console.error('Error converting blob to Uint8Array:', error);
    return null; // or handle the error as you see fit
  }
}

// Example usage with a fetch request that gets a blob
async function fetchBinaryDataAndConvert(url, accessToken) {
  try {
    const response = await fetch(url, {
      headers: {
        'Authorization': `Bearer ${accessToken}` // Assuming you're using Bearer token authentication
      }
    });

    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }
    
    const binaryData = await response.blob(); // Get binary data as a Blob
    const uint8Array = await convertBlobToUint8Array(binaryData); // Convert the blob to Uint8Array
    console.log(uint8Array); // Now you have the data as a Uint8Array
    // Further processing...
  } catch (error) {
    console.error('Failed to fetch and convert binary data:', error);
  }
}

// Example usage: Ensure you replace 'your-binary-data-url' and 'your_access_token' with actual values
fetchBinaryDataAndConvert('your-binary-data-url', 'your_access_token');




function readMessage(bytes) {
    let type   = readInt32LE(bytes, 0); // 
    let length = readInt32LE(bytes, 4); // 

    // check if this was in queue

	switch (type) {
        case RESPONSES.GOT_NOTIFICATIONS:
            let N = bytes[0]
            for (let i = 0; i < N; ++i) {
                readNotification()
            }
            break;

        case RESPONSES.REMOVED_NOTIFICATIONS:
            if (bytes[0] == 1) {
                // find the idx of the removed
                let notification_idx = CONFIG.wsSpareData
                removeNotification(notification_idx)
                CONFIG.wsSpareData = null
            }

            else {
                showRemoveError()
            }
            
            break;

        case RESPONSES.GET_RATINGS:
            let sp = []

            for (let i = 0; i < 9; ++i) {
                let jImsId   = readInt48LE(bytes, (i << 3)); // imageset id [8]
                let jImgIdx  = bytes[(i << 3) + 6]; // image index 0 [9]

                sp.push([jId, jImgIdx0])
            }

            // NOOOO PUT THIS INTO PREFETCH QUEUE
            CONFIG.rating = sp
            SESSION.prefetchQueue = sp
    		break;
    	case RESPONSES.GET_PAIRINGS:
            let sp = []

            for (let i = 0; i < 8; ++i) {
                let id      = readInt48LE(bytes, (i * 10) + 8); // imageset id [8]
                let imgIdx0 = bytes[(i * 10) + 16]; // image index 0 [9]
                let imgIdx1 = bytes[(i * 10) + 17]; // image index 1 [10]

                sp.push([id, imgIdx0, imgIdx1])
            }
            
            CONFIG.pairing = sp
    		break;
        case RESPONSES.GET_IMAGESETS:
            let sp = []

            for (let i = 0; i < imagesetCt; ++i) {
                let id        = readInt48LE(bytes, (i << 5) + ); // imageset id [6]
                let title     = readString(bytes)
                let timestamp = readInt48LE(bytes, (i << 5) + 8); // [12]
                let comments  = readInt32LE(bytes, (i << 5) + 16); // [20]
                let imgCt     = bytes[(i << 5) + 20]; // [21]
                let imgIdx0   = bytes[(i << 5) + 21]; // [22]
                let imgIdx1   = bytes[(i << 5) + 22]; // [23]
                let imgIdx2   = bytes[(i << 5) + 23]; // [24]
                let imgIdx3   = bytes[(i << 5) + 24]; // [25]

                sp.push([id, timestamp, comments, imgCt, imgIdx0, imgIdx1, imgIdx2, imgIdx3])
            }

            CONFIG.imagesets = sp
            break;
        case RESPONSES.GET_IMAGESET_ID:
            // get an imageset and all its images
            let ims = []
            let imageCt = readInt48LE(2 * i); // imageset id
            let titleLen = readInt48LE(2 * i); // imageset title
            let title = readInt48LE(2 * i); // imageset title
            let offsetBytes = 2

            for (let i = 0; i < imageCt; ++i) {
                let id       = readInt48LE(bytes, (i << 5) + 8); // image idx [8]
                let title    = readString(bytes)
                let comments = readInt32LE(bytes, (i << 5) + 16); // comments [12]

                let ratingCt = readInt32LE(bytes, (i << 5) + 20); // comments [16]
                let ratingA  = readInt16LE(bytes, (i << 5) + 24); // comments [18]
                let ratingL  = readInt16LE(bytes, (i << 5) + 26); // comments [20]
                let ratingH  = readInt16LE(bytes, (i << 5) + 28); // comments [22]

                ims.push([id, comments, ratingCt, ratingA, ratingL, ratingH])
            }

            CONFIG.imagesetIDimages = ims
            break;
        case RESPONSES.GET_IMAGE_IDX:
            // read multiple because multiple are sent for speed for batching/click multiple
            let bytesOffset = 1
            for (let i = 0; i < bytes[0]; ++i) {
                bytesOffset = readImageIdx(bytes, bytesOffset);
            }
            break;

        case RESPONSES.GET_IMAGE_IDX_ADVANCED:
            //readImageIdxAdv
            break;

        case RESPONSES.GET_LOGIN_SEED:
            let resp = bytes[0]
            // default, even if there is no username existing, due to 
            // security by obscurity
            if (resp == 0) {
                hideLoginError()
                CONFIG.lSeed = bytes.slice(1, 17)
                showPassword()
            }
            
            else if (resp == 1) {
                hideLoginError()
                CONFIG.lSeed = bytes.slice(1, 17)
                showCode()
            }
            
            else {
                displayError()
            }
            
            break;

        case RESPONSES.GET_LOGIN_FINAL:
            // see if worked
            let resp = bytes[0]
            if (resp == 0) {
                CONFIG.lSeed = null
                CONFIG.lToken = bytes.slice(1, 17);
                hideLoginError()
                gotoHome()
            }
            
            else if (resp == 1) {
                CONFIG.lSeed = bytes.slice(1, 17);
                hideLoginError()
                switchTOTP()
            }

            else if (resp == 2) {
                displayIncorrectPassword()
            }

            else {
                displayIncorrectCode()
            }
            break;

        case RESPONSES.GET_TOTP_FINAL:
            let resp = bytes[0]
            if (resp == 0) {
                hideLoginError()
                CONFIG.lSeed = null
                CONFIG.lToken = bytes.slice(1, 17);
                gotoHome()
            }

            else {
                displayIncorrectCode()
            }
            break;

        case RESPONSES.GET_PROFILE:
            let resp = bytes[0]
            if (resp == 0) {
                let email = readVarstring(bytes, 1)
                let phone = readVarstring(bytes, 1)
                let gender = bytes[offset]
                let age = bytes[offset + 1]
            }

            else {
                
            }
            break;

        case RESPONSES.UPDATED_USER:
            // GOTO HOME...
            modalChangesSaved()
            break;

        case RESPONSES.REGISTERED_USER:
            // GOTO HOME...
            gotoHome()
            break;

        case RESPONSES.CREATED_TICKET:
            showTicketCreated()
            break;

        case RESPONSES.GET_TICKET:
            showTicketCreated()
            break;

        case RESPONSES.END_TICKET:
            showTicketCreated()
            break;

        case RESPONSES.LOGOUT:
        case RESPONSES.DELETED_USER:
            // GOTO HOME...
            clearConfig()
            gotoLogin()
            break;

        case RESPONSES.INITIATE_RESET_PASSWORD:
            // SUCCESSFULLY RESET
            showResetEmailSent()
            break;

        case RESPONSES.RESET_PASSWORD_WITH_ID:
            // SUCCESSFULLY RESET

            CONFIG.lToken = bytes.slice(1, 17);
            gotoHome()
            break;

        case RESPONSES.GET_UPLOAD_IMAGE:
            // Get N upload codes
            let num = bytes[0]

            break;

        case RESPONSES.CREATED_IMAGESET:
            // Get N upload codes
            gotoImageset()

            break;
	}
}


function getSeed(dview) {
	//seed = 
	// show password if needed,

}


function endTest() {

}

function resTest() {

}

