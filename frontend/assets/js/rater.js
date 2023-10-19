function getRates() {
  let divCa = DYZ.cloneNode(true)
  divCa.id = 'Ca';

  let btnBR = BTN.cloneNode(true)
  btnBR.className='btn BR'
  btnBR.id='R0'

  let btnB1=btnBR.cloneNode(true)
  btnB1.id='R1'
  let btnB2=btnBR.cloneNode(true)
  btnB2.id='R2'
  let btnB3=btnBR.cloneNode(true)
  btnB3.id='R3'
  let btnB4=btnBR.cloneNode(true)
  btnB4.id='R4'

  btnBR.innerHTML='😒<br>Eh'
  btnB1.innerHTML='😐<br>Decent'
  btnB2.innerHTML='😃<br>Great'
  btnB3.innerHTML='🤩<br>Stunning'
  btnB4.innerHTML='🤑<br>Brilliant'

  divCa.appendChild(btnBR)
  divCa.appendChild(btnB1)
  divCa.appendChild(btnB2)
  divCa.appendChild(btnB3)
  divCa.appendChild(btnB4)
  return divCa
}


function getUa() {
  let divUa = DIV.cloneNode(true)
  divUa.id = 'Ua';

  // Manually create and append each span
  let spanQa = SPN.cloneNode(true)
  spanQa.id = 'Qa';
  spanQa.className = 'BZ';
  spanQa.textContent = '😓 awkward';
  divUa.appendChild(spanQa);

  let spanQb = spanQa.cloneNode(true)
  spanQb.id = 'Qb';
  spanQb.textContent = '🫥 bad expression';
  divUa.appendChild(spanQb);

  let spanQc = spanQa.cloneNode(true)
  spanQc.id = 'Qc';
  spanQc.textContent = '🖼 bad framing';
  divUa.appendChild(spanQc);

  let spanQd = spanQa.cloneNode(true)
  spanQd.id = 'Qd';
  spanQd.textContent = '🍞 bland';
  divUa.appendChild(spanQd);

  let spanQe = spanQa.cloneNode(true)
  spanQe.id = 'Qe';
  spanQe.textContent = '🏟 distracting';
  divUa.appendChild(spanQe);

  let spanQf = spanQa.cloneNode(true)
  spanQf.id = 'Qf';
  spanQf.textContent = '💨 blurry';
  divUa.appendChild(spanQf);

  let spanQg = spanQa.cloneNode(true)
  spanQg.id = 'Qg';
  spanQg.textContent = '⚡️ bright';
  divUa.appendChild(spanQg);

  let spanQh = spanQa.cloneNode(true)
  spanQh.id = 'Qh';
  spanQh.textContent = '🚊 busy';
  divUa.appendChild(spanQh);

  let spanQi = spanQa.cloneNode(true)
  spanQi.id = 'Qi';
  spanQi.textContent = '🌈 colorful';
  divUa.appendChild(spanQi);

  let spanQj = spanQa.cloneNode(true)
  spanQj.id = 'Qj';
  spanQj.textContent = '🕶 cool';
  divUa.appendChild(spanQj);

  let spanQk = spanQa.cloneNode(true)
  spanQk.id = 'Qk';
  spanQk.textContent = '🌚 dark';
  divUa.appendChild(spanQk);

  let spanQl = spanQa.cloneNode(true)
  spanQl.id = 'Ql';
  spanQl.textContent = '😬 forced smile';
  divUa.appendChild(spanQl);

  let spanQm = spanQa.cloneNode(true)
  spanQm.id = 'Qm';
  spanQm.textContent = '🧂 grainy';
  divUa.appendChild(spanQm);

  let spanQn = spanQa.cloneNode(true)
  spanQn.id = 'Qn';
  spanQn.textContent = '🚨 overedited';
  divUa.appendChild(spanQn);

  let spanQo = spanQa.cloneNode(true)
  spanQo.id = 'Qo';
  spanQo.textContent = '🚶 poor posture';
  divUa.appendChild(spanQo);

  let spanQp = spanQa.cloneNode(true)
  spanQp.id = 'Qp';
  spanQp.textContent = '🔭 too far away';
  divUa.appendChild(spanQp);

  let spanQq = spanQa.cloneNode(true)
  spanQq.id = 'Qq';
  spanQq.textContent = '🔎 too close up';
  divUa.appendChild(spanQq);

  return divUa
}

function getImgsec() {
  let divRIa = DIV.cloneNode(true)
  divRIa.id = 'RIa';
  let divRBa = DIV.cloneNode(true)
  divRBa.id = 'RBa';
  let imgRP = IMG.cloneNode(true)
  imgRP.src='img/laurie.jpg'
  imgRP.alt='Rating picture'

  divRIa.appendChild(divRBa)
  divRIa.appendChild(imgRP)
}

function getButtons() {
  /*
    <div class="y z rel">
      <button id="Dmo" class="dots btn"><span class="d0" id="dd0X"></span><span class="d1" id="dd1X"></span><span class="d2" id="dd2X"></span></button>
      <ul id="rMor" class="dropsort">
        <li><span id="Rpt">Report image</span></li>
      </ul>
      <div class="y">
        <button id="Sk" class="pointer y btn"><span class="f11">Skip</span></button>
        <button id="Sm" class="pointer btn blue"><span class="f11">Submit</span></button>
      </div>
    </div>
  */
}


function getRDa() {
  let divRDa = DIV.cloneNode(true)
  divRDa.id = 'RDa';

  let T0=SPN.cloneNode(true)
  T0.className='fwHeavy'
  T0.innerText='Rating*'

  T1=SPN.cloneNode(true)
  T1.className='fwHeavy'
  T1.innerText='Tags'

  T2=SPN.cloneNode(true)
  T2.className='fwHeavy'
  T2.innerText='Comment'

  txtC=document.createElement('textarea')
  txtC.id='CMa'
  txtC.placeholder='This picture seems...'
  txtC.tabindex='-1'
  txtC.maxlength='255'

  //<textarea id="CMa" placeholder="This picture seems ..." tabindex="-1" maxlength="255"></textarea>

  divRDa.appendChild(T0)
  divRDa.appendChild(getRates())
  divRDa.appendChild(T1)
  divRDa.appendChild(getUa())
  divRDa.appendChild(T2)
  divRDa.appendChild(txtC)
  divRDa.appendChild(getButtons())
}

function getRSa() {
  let Dx = DIV.cloneNode(true)
  Dx.id = 'Ra'

  let divRSa = DIV.cloneNode(true)
  divRSa.id = 'RSa'

}

function getRater() {
  let D2 = DIV.cloneNode(true)
  D2.id = 'Ra'
  D2.className = 'y'
  D2.innerHTML = `
  <div id="RIa">
    <div id="RBa" style="background-image: url('img/laurie.jpg');"></div>
    <img src="img/laurie.jpg" alt="Rating picture">
  </div>
  <div id="RDa">
    <span class="fwHeavy">Rating*</span>
    <div id="Ca" class="y z">
      <button id="R0" class="btn BR">😒<br>Eh</button>
      <button id="R1" class="btn BR">😐<br>Decent</button>
      <button id="R2" class="btn BR">😃<br>Great</button>
      <button id="R3" class="btn BR">🤩<br>Stunning</button>
      <button id="R4" class="btn BR">🤑<br>Brilliant</button>
    </div>
    <span class="fwHeavy">Tags</span>
    <div id="Ua">
      <span id="Qa" class="BZ">😓 awkward</span>
      <span id="Qb" class="BZ">🫥 bad expression</span>
      <span id="Qc" class="BZ">🖼 bad framing</span>
      <span id="Qd" class="BZ">🍞 bland</span>
      <span id="Qe" class="BZ">🏟 distracting</span>
      <span id="Qf" class="BZ">💨 blurry</span>
      <span id="Qg" class="BZ">⚡️ bright</span>
      <span id="Qh" class="BZ">🚊 busy</span>
      <span id="Qi" class="BZ">🌈 colorful</span>
      <span id="Qj" class="BZ">🕶 cool</span>
      <span id="Qk" class="BZ">🌚 dark</span>
      <span id="Ql" class="BZ">😬 forced smile</span>
      <span id="Qm" class="BZ">🧂 grainy</span>
      <span id="Qn" class="BZ">🚨 overedited</span>
      <span id="Qo" class="BZ">🚶 poor posture</span>
      <span id="Qp" class="BZ">🔭 too far away</span>
      <span id="Qq" class="BZ">🔎 too close up</span>
    </div>
    <span class="fwHeavy">Comment</span>
    <textarea id="CMa" placeholder="This picture seems ..." tabindex="-1" maxlength="255"></textarea>
    <div class="y z rel">
      <button id="Dmo" class="dots btn"><span class="d0" id="dd0X"></span><span class="d1" id="dd1X"></span><span class="d2" id="dd2X"></span></button>
      <ul id="rMor" class="dropsort">
        <li><span id="Rpt">Report image</span></li>
      </ul>
      <div class="y">
        <button id="Sk" class="pointer y btn"><span class="f11">Skip</span></button>
        <button id="Sm" class="pointer btn blue"><span class="f11">Submit</span></button>
      </div>
    </div>
  </div>`
  return D2
}
