let languages =
[
	'English',
	'Spanish'
]

function genPrf() {
	Mn.id='Pa'
	Mn.className='oh'
	Mn.innerHTML=`
      <div class="x y narrow rel">
        <div id="SBa" class="BlA">
          <a id="P_" href="/profile">Profile</a>
          <a id="S_" href="/security">Security</a>
          <a id="A_" href="/alerts">Alerts</a>
          <a id="R_" href="/billing">Billing</a>
          <a id="H_" href="/help">Help</a>
        </div>
        <div id="PFa" class="rel">
          <div id="EPa" class="profilePage">
            <h2>Edit Profile</h2>
            <div class="y z">
              <div class="rel" style="width: calc(50% - 10px);">
                <h5>Email</h5>
                <div class="rel">
                  <input id="EMLa" class="" placeholder="Email" type="email" disabled>
                  <svg xmlns="http://www.w3.org/2000/svg" xml:space="preserve" width="24" height="24" viewBox="0 0 528.899 528.899" class="editSvg" id="EiEml"><path fill="#999" d="m328.883 89.125 107.59 107.589-272.34 272.34L56.604 361.465l272.279-272.34zm189.23-25.948-47.981-47.981c-18.543-18.543-48.653-18.543-67.259 0l-45.961 45.961 107.59 107.59 53.611-53.611c14.382-14.383 14.382-37.577 0-51.959zM.3 512.69c-1.958 8.812 5.998 16.708 14.811 14.565l119.891-29.069L27.473 390.597.3 512.69z"/></svg>
                </div>
              </div>
              <div class="rel" style="width: calc(50% - 10px);">
                <h5>Phone</h5>
                <div>
                  <input id="PHNn" class="" placeholder="Phone" type="text">
                </div>
              </div>
            </div>
            <div>
              <h5 class="fwHeavy">Gender*</h5>
              <div id="pGda" class="pilWr y">
                <div class="pilBg pointer"></div>
                <div id="Ff" class="pilIt pointer">Female</div>
                <div id="Mf" class="pilIt pointer">Male</div>
              </div>
            </div>
            <div>
              <h5 class="fwHeavy">Age Range*</h5>
              <div id="pAge" class="pilWr y">
                <div class="pilBg pointer"></div>
                <div id="u0" class="pilIt pointer">18-24</div>
                <div id="u1" class="pilIt pointer">25-29</div>
                <div id="u2" class="pilIt pointer">30-39</div>
                <div id="u3" class="pilIt pointer">40-49</div>
                <div id="u3" class="pilIt pointer">50+</div>
              </div>
            </div>
            <div>
              <h5 class="fwHeavy">Online Habits*</h5>
              <div id="pHbt" class="pilWr y">
                <div class="pilBg pointer"></div>
                <div id="j0" class="pilIt pointer">Rarely</div>
                <div id="j1" class="pilIt pointer">Weekly</div>
                <div id="j2" class="pilIt pointer">Daily</div>
                <div id="j3" class="pilIt pointer">Hourly</div>
              </div>
            </div>
            <button id="savz" class="btn blue">
              Save changes
            </button>
          </div>
          <div id="SCa" class="profilePage">
            <h2>Security</h2>
            <div id="PPa">
              <h4>Password</h4>
                <button id="CH" class="btn blue">Change password</button>
                <button id="CN" class="btn blue">Setup no-pass login</button>
              <div id="CHpw" class="dn">
                <input id="oldPassword" class="" placeholder="Current password" type="password">
                <input id="newPassword0" class="" placeholder="New password" type="password">
                <input id="newPassword1" class="" placeholder="Confirm new password" type="password">
                <button id="CF" class="btn">Change password</button>
              </div>
            </div>
            <div>
              <h4>Two-Factor Authentication</h4>
              <p id="TFa" class="F12">TFA is active.</p>
              <button id="A2F" class="btn gray">Activate two-factor</button>
              <button id="R2F" class="btn blue">Reset two-factor</button>
            </div>
            <div>
              <h4>Login history</h4>
              <div class="y z" style="border-top:1px solid rgba(0,0,0,0.04);padding: 1em 4px">
                <div class="bl">
                  <span class="bl F12">iPhone 13 Pro Max</span>
                  <span class="bl F12">Safari 11</span>
                </div>
                <div class="bl">
                  <span style="margin-left:auto;display: block;text-align: right;" class="F12">69.215.210.45 (Pyongyang, North Korea)</span>
                  <span class="bl F12">January 29, 2017 11:30:50 PM</span>
                </div>
              </div>
            </div>
          </div>
          <div id="Alr">
            <h2>Alerts</h2>
            <div>
              <div class="F12" style="text-align: right;">
                <span>Text</span>
                <span>Email</span>
              </div>
            </div>
            <div class="y toggleNotif">
              <div>
                <h5>Image finished</h5>
                <p class="F12">One image meets rating quota (excessive)</p>
              </div>
              <div class="mla y chbxg">
                <input type="checkbox" style="margin-right:20px" name="imgFinish">
                <input type="checkbox" name="imgFinish">
              </div>
            </div>
            <div class="y toggleNotif">
              <div>
                <h5>Task finished</h5>
                <p class="F12">All images in the entire task finishes testing.</p>
              </div>
              <div class="mla y chbxg">
                <input type="checkbox" style="margin-right:20px" name="taskFinish">
                <input type="checkbox" name="taskFinish">
              </div>
            </div>
            <div class="y toggleNotif">
              <div>
                <h5>Profile change</h5>
                <p class="F12">When you click save changes made to profile.</p>
              </div>
              <div class="mla y chbxg">
                <input type="checkbox" style="margin-right:20px" name="login">
                <input type="checkbox" name="login">
              </div>
            </div>
            <div class="y toggleNotif">
              <div>
                <h5>Support requests</h5>
                <p class="F12">When a support ticket is updated.</p>
              </div>
              <div class="mla y chbxg">
                <input type="checkbox" style="margin-right:20px" name="support">
                <input type="checkbox" name="support">
              </div>
            </div>
            <div class="y toggleNotif">
              <div>
                <h5>Login</h5>
                <p class="F12">Each time you login to the website.</p>
              </div>
              <div class="mla y chbxg">
                <input type="checkbox" style="margin-right:20px" name="login">
                <input type="checkbox" name="login">
              </div>
            </div>
            <div class="y toggleNotif">
              <div>
                <h5>Purchase</h5>
                <p class="F12">Each time a purchase is made.</p>
              </div>
              <div class="mla y chbxg">
                <input type="checkbox" style="margin-right:20px" name="login">
                <input type="checkbox" name="login">
              </div>
            </div>
          </div>
          <div id="Bil">
            <h2>Billing</h2>
            <button>New ticket</button>
            <div>
              <div class="y z" style="border-top:1px solid rgba(0,0,0,0.04);padding: 1em 4px">
                <div class="bl">
                  <h6 class="bl ">Premium subscription (monthly)</h6>
                  <span class="bl F12">January 29, 2017</span>
                </div>
                <div class="bl">
                  <span style="margin-left:auto;display: block;text-align: right;" class="F12">$10.99</span>
                </div>
              </div>
            </div>
          </div>
          <div id="Hlp">
            <h2>Help</h2>
            <button class="btn blue">New ticket</button>
            <div>
              <div class="tkt y z" style="border-top:1px solid rgba(0,0,0,0.04);padding: 1em 4px">
                <h6 class="bl ">From: Support staff</h6>
                <span style="margin-left:auto;display: block;text-align: right;" class="F12">Blah69420jjhadsads adsijijasd</span>
                <span class="bl F12">January 29, 2017</span>
              </div>
            </div>
          </div>
        </div>
      </div>`

}
