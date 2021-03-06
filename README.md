## react-native-sinch-verification

Sinch Verification for react native. http://www.sinch.com

### Installation

#### IOS
1. `npm install react-native-sinch-verification`
2. In the XCode's "Project navigator", right click on project name folder ➜ `Add Files to <...>`
 - Ensure `Copy items if needed` and `Create groups` are checked
3. Go to `node_modules` ➜ `react-native-sinch-verification` ➜ add `SinchVerificationIOS` folder
4. Add the dependency frameworks as described [here](https://www.sinch.com/docs/verification/ios#addthesinchverificationframework) (The `SinchVerication.framework` can be found in this package, under the `SinchVericationSDK` folder)

#### Android
1. `npm install react-native-sinch-verification`
2. `rnpm link react-native-sinch-verification` - (run `npm install -g rnpm` if required)
3. require the permissions as specified [here](https://www.sinch.com/docs/verification/android/#permissions)

### Usage

```javascript
var SinchVerification = require('react-native-sinch-verification');
var custom = "A custom string to be sent to your server backend, through Sinch's callback URL";

// init with app key
SinchVerification.init('your-app-key');

// sms verification
SinchVerification.sms('your-phone-number-without-country-code', custom, (err, res) => {
  if (!err) {
      // for android, verification is done, because the sms has been read automatically
      // for ios, this means the sms has been sent out, you need to call verify with the received code
  }
});

// verify the received code (not needed on android)
SinchVerification.verify('the-received-code', (err, res) => {
  if (!err) {
      // done!
  }
});

// flash call verification (android only)
SinchVerification.flashCall('your-phone-number-without-country-code', custom, (err, res) => {
  if (!err) {
      // done!
  }
});

```
