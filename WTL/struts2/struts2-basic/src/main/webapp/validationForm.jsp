<%@ taglib prefix="s" uri="/struts-tags"%>
<!DOCTYPE html>
<html>
<head>
	<title>Validation Form</title>
	<link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
	<style type="text/css">
		.error { color: red; }
	</style>
</head>
<body>
	<div class="container">
		<h2>Validation Form</h2>
		<s:form action="validateForm" method="post">
			<div class="form-group">
				<label for="name">Name:</label>
				<s:textfield name="name" cssClass="form-control" placeholder="Enter name" />
				<s:if test="hasActionErrors()">
					<s:actionerror />
				</s:if>
			</div>
			<div class="form-group">
				<label for="email">Email:</label>
				<s:textfield name="email" cssClass="form-control" placeholder="Enter email" />
				<s:if test="hasActionErrors()">
					<s:actionerror />
				</s:if>
			</div>
			<div class="form-group">
				<label for="phone">Phone:</label>
				<s:textfield name="phone" cssClass="form-control" placeholder="Enter phone number" />
				<s:if test="hasActionErrors()">
					<s:actionerror />
				</s:if>
			</div>
			<button type="submit" class="btn btn-primary">Submit</button>
		</s:form>
	</div>
</body>
</html>