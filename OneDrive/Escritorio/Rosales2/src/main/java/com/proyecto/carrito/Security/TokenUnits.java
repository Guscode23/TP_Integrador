package com.proyecto.carrito.Security;
import java.util.Collections;
import java.util.Date;
import java.util.Map;

import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.JwtBuilder;
import io.jsonwebtoken.JwtException;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.security.Keys;


public class TokenUnits {

	private final static String ACCESS_TOKEN_SECRET="dhdhduwu388838383hshssjd";
	private final static Long seconds= 2_592_000L;
	
	public static String createToken(String nombre,String email)
	{
		long expirationTime=seconds*1_0000;
		Date expirationDate=new Date(System.currentTimeMillis()+ expirationTime);
		
		Map<String,Object> extra= new HashMap<>();
		extra.put("nombre",nombre);
		
		return Jwts.builder()
				.setSubject(email)
				.setExpiration(expirationDate)
				.addClaims(extra)
				.signWith(Keys.hmacShaKeyFor(ACCESS_TOKEN_SECRET.getBytes()))
		        .compact();
		}
	
	public static UsernamePasswordAuthenticationToken getAuthentication(String token) {
		
		try {
			
			Claims claims= Jwts.parserBuilder()
					.setSigningKey(ACCESS_TOKEN_SECRET.getBytes())
					.build()
					.parseClaimsJwt(token)
					.getBody();
				
		    String email=claims.getSubject();
				
		return new UsernamePasswordAuthenticationToken(email,null,Collections.emptyList());
         }catch(JwtException e){
			return null;
		}
		
		
		
		
				
		
	}
	
	
	
}
