document.addEventListener('touchstart', handleTouchStart, false);        
document.addEventListener('touchmove', handleTouchMove, false);
let rateData = document.getElementById('rate-data')
var xDown = null;                                                        
var yDown = null;

function getTouches(evt) {
  return evt.touches ||             // browser API
         evt.originalEvent.touches; // jQuery
}                                                     
                                                                         
function handleTouchStart(evt) {
    const firstTouch = getTouches(evt)[0];                                      
    xDown = firstTouch.clientX;                                      
    yDown = firstTouch.clientY;                                      
};                                                
                                                                         
function handleTouchMove(evt) {
    if (!xDown || !yDown) { return; }

    var xUp = evt.touches[0].clientX;                                    
    var yUp = evt.touches[0].clientY;

    var xDiff = xDown - xUp;
    var yDiff = yDown - yUp;
    console.log(evt.target)
    console.log(xDiff, yDiff)
    console.log(rateData.contains(evt.target))
                                                                         
    if ( Math.abs( xDiff ) > Math.abs( yDiff ) ) {/*most significant*/
        if (xDiff > 0) {
            /* right swipe */ 
        } else {
            /* left swipe */
        }                       
    } else {
        if (yDiff > 0) {
            console.log('down swipe')
            /* down swipe */ 
        } else { 
            console.log('up swipe')
            rateData.className = 'tagsLevel'
            /* up swipe */
        }                                                                 
    }
    /* reset values */
    xDown = null;
    yDown = null;                                             
};