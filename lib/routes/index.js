exports.serveIndex = function (app, staticFolder) {
  app.get('*', function (req, res) {
    res.sendFile('index.html', { root: staticFolder });
  });
};