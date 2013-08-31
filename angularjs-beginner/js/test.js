var app = angular.module('angularjs-beginner-app', []);
app.controller('angular-beginner-controller', function($scope){
	$scope.person = {
		name: "hsgui"
	};
});

app.controller('ParentController', function($scope){
	$scope.person = {
		greeted: false
	};
});

app.controller('ChildController', function($scope){
	$scope.sayHello = function(){
		$scope.person.greeted = true;
	};
});