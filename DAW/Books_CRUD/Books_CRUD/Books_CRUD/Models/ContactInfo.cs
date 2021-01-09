using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Books_CRUD.Models
{
    public class ContactInfo
    {
        public int Id { get; set; }
        public String PhoneNumber { get; set; }
        public virtual Publisher Publisher { get; set; }
    }
}