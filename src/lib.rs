use std::ffi::CStr;
use std::os::raw::c_char;

#[no_mangle]
pub extern "C" fn validate_password(c_username: *const c_char, c_password: *const c_char) -> i32 {
  let password: String = unsafe { CStr::from_ptr(c_password).to_string_lossy().into_owned() };
  let username: String = unsafe { CStr::from_ptr(c_username).to_string_lossy().into_owned() };
  println!("username: <{:?}>, password: <{:?}>", username, password);
  if password.is_empty() {
    return -1;
  }
  return 0;
}
