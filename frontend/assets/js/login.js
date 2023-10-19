function logins() {
	let divYa=DIV.cloneNode(true)
	let divBG=DIV.cloneNode(true)
	divBG.id='bger'
	let divLP=DIV.cloneNode(true)
	divLP.id='loginpanel'
	let sig=H2.cloneNode(true)

	let lbe=LBL.cloneNode(true)
	lbe.innerText='Phone or Email'

	`<div id="Ya">
      <div id="bger">
      </div>
      <div id="loginpanel">
        <h1 style="font-size: 20px"><span id="signupTitle">Sign up to get started</span><span id="loginTitle">Log in</span></h1>
        <form>
          <label>Phone or Email</label>
          <div class="iS" style="width: 100%;">
            <input id="emailSignup" autocomplete="email" name="email" type="email" value="" placeholder="user@example.com"  style="width: 100%;box-sizing: border-box;"/>
          </div>
          <div style="margin-top: 1em">
            <label>Password</label>
            <div class="iS">
              <input id="passwordSignup" name="password" type="password" value="" placeholder="Password" style="width: 100%;box-sizing: border-box;"/>
            </div>
          </div>
        </form>
        <button id="signupeq">Sign up</button>
        <div style="width:100%">
          <p id="WrPa" class="meta red">Wrong password</p>
          <div class="PrPa">By signing up, you agree to our <a href="https://frame.io/terms/" target="_blank">Terms of Service</a> and <a href="https://frame.io/privacy" target="_blank">Privacy Policy.</a>
          </div>
          <p class="meta">Already have an account? <a href="/welcome">Log in.</a></p>
        </div>
      </div>
    </div>`
}