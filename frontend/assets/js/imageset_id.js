

function generateImagesetMetadata(title, imageId, statusInt) {/*
  var tmta = \
   `<div id="TMta">
      <div class="y z">
        <span id="RQ">Rating Test</span>
        <span id="RQ">ts_0123456789abcdef</span>
      </div>
      <div  class="rel y BB">
        <h2 style="font-weight: 600;width: 100%;padding-bottom: 12px;" >Sarah Lasalle <span class="BW">Running</span></h2>
        <button id="dtz" class="dots btn L16"><span class="d0" id="dd0X"></span><span class="d1" id="dd1X"></span><span class="d2" id="dd2X"></span></button>
        <ul id="bblDropdown" class="dropsort">
          <li><span id="editM">Restart test...</span></li>
          <li><span id="editM">Resume test</span></li>
          <li><span id="editM">Pause test</span></li>
          <li><span id="editM">Edit test</span></li>
          <li><span id="deleN">Delete test</span></li>
        </ul>
      </div>
      <div class="y t16">
        <div class="BY r16"><span class="F12 ST">total votes</span><span class="bl">45</span></div>
        <div class="BY L16 r16"><span class="F12 ST">total votes</span><span class="bl">45</span></div>
        <div class="L16"><span class="F12 ST">created</span><span class="bl">Jan 17, 2017</span></div>
      </div>
      <span style="font-size: 11px"></span>
      <div class="y rel">
      </div>
    </div>`;*/

  // Create the outermost div

  // First inner div with classes 'y' and 'z'
  let spanRQ=SPN.cloneNode(true);
  spanRQ.id='RQ';
  spanRQ.textContent='Rating Test';

  let spanRQ2=SPN.cloneNode(true);
  spanRQ2.id='RQ2';
  spanRQ2.textContent='ts_' + hex(imageId);

  let divYz=DYZ.cloneNode(true);
  divYz.appendChild(spanRQ);
  divYz.appendChild(spanRQ2);

  let spanBW=SPN.cloneNode(true)
  spanBW.className = 'BW';
  spanBW.textContent = STATUS[statusInt];//'Running'; // status

  let imagesetTitle = H2.cloneNode(true);
  imagesetTitle.id = 'imagesetTitle'
  imagesetTitle.textContent=title; // title
  imagesetTitle.appendChild(spanBW);

  // hamburger
  let hamburgerCtrl = HMB.cloneNode(true)
  hamburgerCtrl.id='dtz'
  hamburgerCtrl.className='dots btn L16'

  let ulBblDropdown = UL.cloneNode(true)
  ulBblDropdown.id = 'bblDropdown';
  ulBblDropdown.className = 'dropsort';

  ////
  const cmds = ['Restart test','Resume test','Pause test','Edit test','Delete test']
  for (let i = 0; i < 5; ++i) {
    let li = LI.cloneNode(true)
    let span = SPN.cloneNode(true)
    span.id = `edit${i}`;
    span.textContent = cmds[i];
    li.appendChild(span);
    ulBblDropdown.appendChild(li);
  }
  ////

  // Second inner div with classes 'rel', 'y', and 'BB'
  let divRelYBB=DIV.cloneNode(true);
  divRelYBB.className='rel y BB';
  divRelYBB.appendChild(imagesetTitle)
  divRelYBB.appendChild(hamburgerCtrl)
  divRelYBB.appendChild(ulBblDropdown)

  // The third div with classes 'y' and 't16'
  let divYT16=DIV.cloneNode(true)
  divYT16.className = 'y t16';


  const deet = ['total images','total votes','created']
  const clsn = ['BY r16','BY L16 r16','L16']
  const txtc = [imageCt,voteCt,date2str(unix)]
  for (let i = 0; i < 3; ++i) {
    let div = DIV.cloneNode(true)
    div.className = clsn[i]
    
    let spanST = SPN.cloneNode(true)
    spanST.className = 'F12 ST';
    spanST.textContent = deet[i];
    
    let spanBl = SPN.cloneNode(true)
    spanBl.className = 'bl';
    spanBl.textContent = txtc[i]
    
    div.appendChild(spanST);
    div.appendChild(spanBl);
    divYT16.appendChild(div);
  }


  let spanFontSize = SPN.cloneNode(true)
  spanFontSize.style.fontSize = '11px';

  let divTMta=DIV.cloneNode(true)
  divTMta.id='TMta';
  divTMta.appendChild(divYz);
  divTMta.appendChild(divRelYBB);
  divTMta.appendChild(divYT16);
  divTMta.appendChild(spanFontSize);

  DOMSHORTCUTS.imagesetTitle = imagesetTitle

  return divTMta
}

function updateImagesetMetadata(title, totalImages, totalVotes, created)
{
  DOMSHORTCUTS.imagesetTitle.firstChild.nodeValue = title
  DOMSHORTCUTS.totalImages.firstChild.nodeValue = 
  DOMSHORTCUTS.totalVotes.firstChild.nodeValue = 
  DOMSHORTCUTS.created.firstChild.nodeValue = 
}

// image within imageset/:id
function imageIndiv(imagesetId, idx, score, votes) {
  const imgMat = IMG.cloneNode(true)
  imgMat.src = "img" + hex(imagesetId) + hex(idx) + '.jpg'
  imgMat.alt = 'Image ' + idx

  const imgWrap = AX.cloneNode(true)
  imgWrap.className = ''
  imgWrap.href = '/' + idx
  imgWrap.appendChild(imgMat)

  const score = SPN.cloneNode(true)
  score.className = 'ascore'
  score.firstChild.nodeValue = score / 100

  const comCt = score.cloneNode(true)
  comCt.className = 'acomm'
  comCt.firstChild.nodeValue = votes + ' votes'

  const ctWrap = DIV.cloneNode(true)
  ctWrap.className = 'mla'
  ctWrap.appendChild(comCt)

  const mtaWrap = DIV.cloneNode(true)
  mtaWrap.className = 'W D imgData abs y z'
  mtaWrap.appendChild(score)
  mtaWrap.appendChild(ctWrap)

  const imgItem = DIV.cloneNode(true)
  imgItem.className = 'taskItem rel'
  imgItem.appendChild(imgWrap)
  imgItem.appendChild(mtaWrap)

  return imgItem
}


function updateImageIndiv(array, idx, title, totalImages, totalVotes, created)
{
  array[idx].imgWrap.href = ''
  array[idx].imgMat.src = ''
  array[idx].imgMat.alt = ''
  array[idx].score.firstChild.nodeValue = '' + 'votes'
  array[idx].comCt.firstChild.nodeValue = '' + 'votes'
}


function getImagesetId()
{
  Mn.id='Ta';
  Mn.className='oh';

  Mn.children[0].appendChild(generateImagesetMetadata())
  var Tls=DIV.cloneNode(true)
  Tls.id='TLS'
  Tls.className='G'
  
  for (let i = 0; i < CONFIG.images.length; ++i) {
    let imgObj = CONFIG.images
    Tls.appendChild(imageIndiv())
  }

  Mn.children[0].appendChild(Tls)
}
