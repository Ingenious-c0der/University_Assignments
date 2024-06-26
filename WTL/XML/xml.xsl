<?xml version = "1.0" encoding = "utf-8"?>
<xsl:stylesheet version = "1.0"
xmlns:xsl = "http://www.w3.org/1999/XSL/Transform">
<xsl:template match = "/">
<html>
<body>
<h2>XML to HTML</h2>
<table border = "1">
<tr bgcolor = "#9acd32">
<th>Keyboard Name</th>
<th>Manufacturer</th>
<th>Cost</th>
</tr>
<xsl:for-each select = "KeyBoardStore/Keyboard">
<tr>
<td>
<xsl:value-of select = "KeyBoardModel"/>
</td>
<td>
<xsl:value-of select = "KeyBoardBrand"/>
</td>
<td>
<xsl:value-of select = "KeyBoardPrice"/>
</td>
</tr>
</xsl:for-each>
</table>
</body>
</html>
</xsl:template>
</xsl:stylesheet>