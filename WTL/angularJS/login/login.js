var app = angular.module('loginApp', []);

app.controller('loginCtrl', function($scope) {
  $scope.submitForm = function() {
    // Perform login validation
    if ($scope.email == 'sagarabhyankar18@gmail.com' && $scope.password == '1234') {
      alert('Login successful');
    } else {
      alert('Invalid login credentials');
    }
  };
});