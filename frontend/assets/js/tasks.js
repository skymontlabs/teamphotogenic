
function cr8_dt() {
  let DT = BTN.cloneNode(true)
  DT.className = 'dots btn L16'
  let D0 = SPN.cloneNode(true)
  D0.className = 'd0'
  let D1 = SPN.cloneNode(true)
  D1.className = 'd1'
  let D2 = SPN.cloneNode(true)
  D2.className = 'd2'

  DT.appendChild(D0)
  DT.appendChild(D1)
  DT.appendChild(D2)

  return DT
}

let DZ = cr8_dt()


function filterStatus() {
  let Pr = DIV.cloneNode(true)
  Pr.id='imagesetFilterbar'
  let Bn = BTN.cloneNode(true)
  let Sx = SPN.cloneNode(true)
  let Zx = H4.cloneNode(true)
  Bn.id='Bv0'
  Bn.className='btn'
  Sx.id='Bw0'
  Sx.className='F12 ST'
  Sx.innerText='All'
  Zx.id='Bx0'
  Zx.innerText='14'
  Bn.appendChild(Sx)
  Bn.appendChild(Zx)
  let b1 = Bn.cloneNode(true)
  b1.id='Bv1'
  b1.children[0].id='Bw1'
  b1.children[0].innerText='Running'
  b1.children[1].id='Bx1'
  b1.children[1].innerText='1'
  let b2 = Bn.cloneNode(true)
  b2.id='Bv2'
  b2.children[0].id='Bw2'
  b2.children[0].innerText='Paused'
  b2.children[1].id='Bx2'
  b2.children[1].innerText='12'
  let b3 = Bn.cloneNode(true)
  b3.id='Bv3'
  b3.children[0].id='Bw3'
  b3.children[0].innerText='Finished'
  b3.children[1].id='Bx3'
  b3.children[1].innerText='1'
  Bn.className='btn A'


  Pr.appendChild(Bn)
  Pr.appendChild(b1)
  Pr.appendChild(b2)
  Pr.appendChild(b3)

  //Ta.children[0].appendChild(Pr)
  return Pr
}


function taskData() {
  const taskItem = DIV.cloneNode(true)
  taskItem.className = 'taskItem'

  const imgWrap = DIV.cloneNode(true)
  imgWrap.className = 'imgWrp'
  const imgMat = AX.cloneNode(true)
  imgMat.style.background = 'url("img/laurie.jpg")'
  imgMat.style.backgroundSize = 'cover'
  imgMat.href = '/imageID'
  for (var i = 0; i < 3; ++i) {
    const imgClone = imgMat.cloneNode(true)
    imgClone.style.height = '130px'
    imgWrap.appendChild(imgClone)
  }
  imgMat.className = 'fillImg'


  const txtWrap = DIV.cloneNode(true)
  txtWrap.className = 'y'
  const title = document.createElement('h6')
  title.innerText = 'seggs'
  const imgCt = SPN.cloneNode(true)
  imgCt.className = 'dtpt'
  imgCt.innerText = '13 images'
  const time = document.createElement('time')
  time.innerText = '5y'
  const dtv = DZ.cloneNode(true)

  //<button id="dropdownDotsX" class="dots btn border"><span class="dlef" id="dd0X">
  //</span><span class="dmid" id="dd1X"></span><span class="drig" id="dd2X"></span></button>


  txtWrap.appendChild(title)
  txtWrap.appendChild(imgCt)
  txtWrap.appendChild(time)
  txtWrap.appendChild(dtv)


  taskItem.appendChild(imgMat)
  taskItem.appendChild(imgWrap)
  taskItem.appendChild(txtWrap)

  return taskItem
}



function testidmta () {/*
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
  let divTMta=DIV.cloneNode(true)
  divTMta.id='TMta';

  // First inner div with classes 'y' and 'z'
  let divYz=DYZ.cloneNode(true);
  let spanRQ=SPN.cloneNode(true);
  spanRQ.id='RQ';
  spanRQ.textContent='Rating Test';
  let spanRQ2=SPN.cloneNode(true);
  spanRQ2.id='RQ2';
  spanRQ2.textContent='ts_0123456789abcdef';
  divYz.appendChild(spanRQ);
  divYz.appendChild(spanRQ2);

  // Second inner div with classes 'rel', 'y', and 'BB'
  let divRelYBB=DIV.cloneNode(true);
  divRelYBB.className='rel y BB';

  let h2 = H2.cloneNode(true);
  h2.textContent='Sarah Lasalle';

  let spanBW = SPN.cloneNode(true)
  spanBW.className = 'BW';
  spanBW.textContent = 'Running'; // status
  h2.appendChild(spanBW);

  //right one
  let buttonDtz = DZ.cloneNode(true)
  buttonDtz.id='dtz'
  buttonDtz.className='dots btn L16'

/*
  let buttonDtz = document.createElement('button');
  buttonDtz.id = 'dtz';
  buttonDtz.className = 'dots btn L16';
  ['d0', 'd1', 'd2'].forEach(cls => {
      let span = SPN.cloneNode(true)
      span.className = cls;
      buttonDtz.appendChild(span);
  });
*/

  let ulBblDropdown = UL.cloneNode(true)
  ulBblDropdown.id = 'bblDropdown';
  ulBblDropdown.className = 'dropsort';
  ['Restart test','Resume test','Pause test','Edit test','Delete test'].forEach((text, index) => {
      let li = document.createElement('li');
      let span = SPN.cloneNode(true)
      span.id = `edit${index}`;
      span.textContent = text;
      li.appendChild(span);
      ulBblDropdown.appendChild(li);
  });

  divRelYBB.appendChild(h2)
  divRelYBB.appendChild(buttonDtz)
  divRelYBB.appendChild(ulBblDropdown)

  // The third div with classes 'y' and 't16'
  let divYT16=DIV.cloneNode(true)
  divYT16.className = 'y t16';

  ['total images','total votes','created'].forEach((text, index) => {
    let div = DIV.cloneNode(true)
    div.className = (index === 0 ? 'BY r16' : (index === 1 ? 'BY L16 r16' : 'L16'));
    
    let spanST = SPN.cloneNode(true)
    spanST.className = 'F12 ST';
    spanST.textContent = text;
    
    let spanBl = SPN.cloneNode(true)
    spanBl.className = 'bl';
    spanBl.textContent = (index === 2 ? 'Jan 17, 2017' : '45');
    
    div.appendChild(spanST);
    div.appendChild(spanBl);
    divYT16.appendChild(div);
  });

  let spanFontSize = SPN.cloneNode(true)
  spanFontSize.style.fontSize = '11px';

  //let divYRel = DIV.cloneNode(true)
  //divYRel.className = 'y rel';

  divTMta.appendChild(divYz);
  divTMta.appendChild(divRelYBB);
  divTMta.appendChild(divYT16);
  divTMta.appendChild(spanFontSize);
  //divTMta.appendChild(divYRel);
  return divTMta
}


function dropdownValue(ulid,chld,chldct,acv,baseval) {
  /*
  <ul id="sortDropdown" class="dropsort show active A">
    <li id="Sd0" class="noselect active">Average score</li>
    <li id="Sd1" class="noselect">Median score</li>
    <li id="Sd2" class="noselect">Date created</li>
    <li id="Sd3" class="noselect">Date created</li>
  </ul>

<div class="dropdownSelector">
  <span id="sortMethodV" class="selClick crt">Average score</span>
  <ul id="sortDropdown" class="dropsort">
    <li id="Sd0" class="noselect active">Average score</li>
    <li id="Sd1" class="noselect">Median score</li>
    <li id="Sd2" class="noselect">Date created</li>
    <li id="Sd3" class="noselect">Date created</li>
  </ul>
</div>

  */

  let DS=DIV.cloneNode(true)
  DS.className='dropdownSelector'
  
  let SM=SPN.cloneNode(true)
  SM.id='sortMethodV'
  SM.className='selClick crt'
  SM.innerText=chld[acv]

  let U=UL.cloneNode(true)
  U.id=ulid
  U.className='dropsort'
  for (var i = 0; i < chldct; i+=1) {
    let L=LI.cloneNode(true)
    L.id = 'Sd' + String.fromCharCode(baseval + i)
    L.className = 'noselect'
    L.innerText=chld[i]
    U.appendChild(L)
  }
  U.children[acv].className='noselect active'

  SM.innerText=chld[acv]

  DS.appendChild(SM)
  DS.appendChild(U)

  return DS
}



function getTestNav() {
  var testnav=DIV.cloneNode(true) 
  var TsT=H2.cloneNode(true)
  testnav.className='wrapsort y z rel BB'
  TsT.id='Fa'
  TsT.innerText='Tests'
  testnav.appendChild(TsT)
  testnav.appendChild(dropdownValue('sortDropdown',['Date Added','Last Modified','# images'],3,0,48))

  return testnav
}

function getAllTests() {
  Mn.id='Ta'

  Mn.children[0].appendChild(getTestNav())
  Mn.children[0].appendChild(filterStatus())
  
  var Tls=DIV.cloneNode(true)
  Tls.id='TLS'
  Tls.className='G'
  Tls.appendChild(taskData())

  Mn.children[0].appendChild(Tls)
}

function imageIndiv()
{
  const imgItem = DIV.cloneNode(true)
  imgItem.className = 'taskItem rel'

  const imgWrap = AX.cloneNode(true)
  imgWrap.className = ''
  imgWrap.href = '/imageID'
  const imgMat = document.createElement('img')
  imgMat.src = 'img/laurie.jpg'
  imgMat.alt = 'Sample image'
  imgWrap.appendChild(imgMat)


  const mtaWrap = DIV.cloneNode(true)
  mtaWrap.className = 'W D imgData abs y z'

  const score = SPN.cloneNode(true)
  
  const ctWrap = DIV.cloneNode(true)
  const comCt = score.cloneNode(true)
  comCt.className = 'acomm'
  score.className = 'ascore'
  score.innerText = '5.69'
  ctWrap.className = 'mla'
  comCt.innerText = '13 votes'

  ctWrap.appendChild(comCt)
  mtaWrap.appendChild(score)
  mtaWrap.appendChild(ctWrap)

  imgItem.appendChild(imgWrap)
  imgItem.appendChild(mtaWrap)

  return imgItem
}


function getPaired() {
  /*
  <div id="Xa" class="">
    <div class="x">
      <div id="RSa">
        <div id="IWa" class="PI">
          <img id="IMa" src="img/laurie.jpg">
        </div>
        <div id="IWb" class="PI">
          <img id="IMb" src="img/lake.jpg">
        </div>
      </div>
    </div>
  </div>
  */
  // Create the outermost div
  //let divXa=DIV.cloneNode(true);
  Mn.id='Xa';

  // Create the child div with class 'x'
  let divX=Mn.children[0]

  // Create the div with id 'RSa'
  let divRSa=DIV.cloneNode(true)
  divRSa.id='RSa';

  // Create the first inner div with id 'IWa' and class 'PI'
  let divIWa=DIV.cloneNode(true)
  divIWa.id='IWa';
  divIWa.className='PI';

  // Create the img inside 'IWa'
  let imgIMa=document.createElement('img');
  imgIMa.id='IMa';
  imgIMa.src='img/laurie.jpg';

  // Append imgIMa to divIWa
  divIWa.appendChild(imgIMa);

  // Create the second inner div with id 'IWb' and class 'PI'
  let divIWb = DIV.cloneNode(true)
  divIWb.id = 'IWb';
  divIWb.className = 'PI';

  // Create the img inside 'IWb'
  let imgIMb = document.createElement('img');
  imgIMb.id = 'IMb';
  imgIMb.src = 'img/lake.jpg';

  // Append imgIMb to divIWb
  divIWb.appendChild(imgIMb);

  // Append divIWa and divIWb to divRSa
  divRSa.appendChild(divIWa);
  divRSa.appendChild(divIWb);

  // Append divRSa to divX
  divX.appendChild(divRSa);

}



function getTestID() {
  Mn.id='Ta';
  Mn.className='oh';

  Mn.children[0].appendChild(testidmta())
  var Tls=DIV.cloneNode(true)
  Tls.id='TLS'
  Tls.className='G'
  Tls.appendChild(imageIndiv())
  Mn.children[0].appendChild(Tls)

}




