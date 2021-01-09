using Books_CRUD.Models;
using Books_CRUD.Models.Database;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Books_CRUD.Controllers
{
    public class HomeController : Controller
    {
        private DbCtx db = new DbCtx();
        public ActionResult Index()
        {
            Book book = new Book
            {
                Title = "Gone with the wind",
                Author = "Margaret Mitchell",
                Date = DateTime.Now
            };
            db.Books.Add(book);
            db.SaveChanges();
            return View();
        }

        public ActionResult About()
        {
            ViewBag.Message = "Your application description page.";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }
    }
}