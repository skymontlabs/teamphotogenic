function addnav() {
  let nav = document.createElement('nav')
  nav.id = 'Na'
  nav.innerHTML=`
      <div class="x y z nomax rel">
        <div id="La" class="noselect">
          <div id="Lb" class="noselect crt rel">
            <span id="Tb" class="noselect">team</span><span id="Pb" class="noselect">photogenic</span>
          </div>
          <div id="Da" class="dropdown BlA">
            <a id="r_" href="/">Rating</a>
            <a id="p_" href="/paired">Paired</a>
          </div>
        </div>
        <button id="Bc" class="rel"></button>
        <div id="Ja" class="y z">
          <button id="Pd" class="btn rel blue" style="margin: 24px 0px;">Experiment</button>
          <button id="Je" class="rel db">
            <svg id="Ke" class="pointer" height="16" width="16" viewBox="0 0 16 16" xmlns="http://www.w3.org/2000/svg"><path id="Le" fill="#414552" d="M5.55 14h4.9a2.5 2.5 0 0 1-4.9 0zM13 9.066l1.216 1.232A1 1 0 0 1 13.504 12H2.496a1 1 0 0 1-.712-1.702L3 9.066V5a5 5 0 1 1 10 0z" fill-rule="evenodd"></path></svg>
            <div id="dea" class="dropdown">
              <div class="y">
                <span class="dropHd">Notifications</span>
                <a class="btn blue" style="

    margin-left: auto;
    margin-right: 13px;
    " href="/notifications">See All</a>
              </div>
              <hr class=""/>
              <ul id="nla">
              </ul>
            </div>
          </button>
          <button id="Jf" type="button" data-testid="user-avatar" class="db">
            <svg id="Kf" class="pointer"  height="16" width="16" viewBox="0 0 16 16" xmlns="http://www.w3.org/2000/svg"><path id="Lf" fill="#414552" d="M8 11a5.698 5.698 0 0 0 3.9-1.537l1.76.66A3.608 3.608 0 0 1 16 13.5V15a1 1 0 0 1-1 1H1a1 1 0 0 1-1-1v-1.5c0-1.504.933-2.85 2.34-3.378l1.76-.66A5.698 5.698 0 0 0 8 11zM7.804 0h.392a3.5 3.5 0 0 1 3.488 3.79l-.164 1.971a3.532 3.532 0 0 1-7.04 0l-.164-1.97A3.5 3.5 0 0 1 7.804 0z" fill-rule="evenodd"></path></svg>
            <div id="dfa" class="dropdown bsbx BlA">
              <a id="Ep_" href="/tasks">Tasks</a>
              <a id="Ep_" href="/profile">Settings</a>
              <a id="Su_" href="/support">Support</a>
              <a id="By_" href="/credits">Credits</a>
              <a id="Gp_" href="/premium">Premium</a>
              <span id="Sg" class="point">Sign Out</span>
            </div>
          </button>
        </div>
      </div>`
  return nav
}


NN=addnav()
document.body.insertBefore(NN, document.body.firstChild);
