angular.module('registrationApp', [])
  .controller('registrationCtrl', function($scope) {
    $scope.user = {};

    $scope.submitForm = function() {
      if ($scope.registrationForm.$valid) {
        alert('Form submitted successfully!');
      } else {
        alert('Please correct the errors in the form.');
      }
    };
  });